#include "baulicht.h"
#include "blink.h"
#include "text.h"
#include "baulichtexecutor.h"
#include "settings.h"
#include "../output/pluginmanager.h"

#include <QDBusConnection>
#include <QTimer>
#include <QDebug>

#include "../output/onoff_gpio.h"

class Baulicht::Private : public QObject
{
    Q_OBJECT

public:
    Private()
    : settings(NULL)
    , mode(0)
    , lastTextId(0)
    , currentTextObject(-1)
    , currentTextPosition(0)
    {
        connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
        timer.setInterval(300);
    }

    // Properties
    Settings *settings;

    int mode;
    bool paused;
    QStringList texts;

    int lastTextId;

    QString currentText;
    int currentTextPosition;
    int currentTextObject;

    BaulichtExecutor executor;

    QTimer timer;
    QList<Text*> childTexts;

    OnOffMorse morse;

public slots:
    void onPauseChanged();
    void timeout();
    void onDitChanged(int dit);
};

void Baulicht::Private::onPauseChanged()
{
    timer.start();
}

void Baulicht::Private::timeout()
{
    // Reset to nothing if there are no texts
    if (childTexts.isEmpty()) {
        currentTextObject = -1;
        return;
    } else if (currentTextObject == -1) {
        currentTextObject = 0;
        currentTextPosition = 0;
        currentText = executor.convertToMorse(childTexts.at(0)->text());

        qDebug() << "Current text is now" << childTexts.at(0)->text();
    }

    const QChar c = currentText.at(currentTextPosition);
    bool on = (c == '=');

    qDebug() << (on ? "on" : "off");
    morse.setOn(on);

    // Text length exceeded, take the next text
    if (++currentTextPosition >= currentText.size()) {

        // Text objects exceeded, start at the beginning
        if (++currentTextObject >= childTexts.size()) {
            currentTextObject = -1;
        } else {
            // Update the current text
            currentText = executor.convertToMorse(childTexts.at(currentTextObject)->text());
            currentTextPosition = 0;

            qDebug() << "Current text is now" << childTexts.at(currentTextObject)->text();
        }
    }
}

void Baulicht::Private::onDitChanged(int dit)
{
    timer.setInterval(dit);
}

Baulicht::Baulicht(QObject *parent)
: QObject(parent)
, d(new Private)
{
    connect(this, SIGNAL(pausedChanged(bool)), d, SLOT(onPauseChanged()));
}

Baulicht::~Baulicht()
{
    delete d;
}

void Baulicht::setSettings(Settings *settings)
{
    if (d->settings == settings)
        return;

    if (d->settings) {
        disconnect(settings, SIGNAL(ditChanged(int)), d, SLOT(onDitChanged(int)));
    }

    d->settings = settings;

    if (d->settings) {
        connect(settings, SIGNAL(ditChanged(int)), d, SLOT(onDitChanged(int)));

        // Update the value immediately
        d->onDitChanged(settings->dit());
    }
}

Settings *Baulicht::settings() const
{
    return d->settings;
}

void Baulicht::setMode(int mode)
{
    if (d->mode != mode) {
        d->mode = mode;
        emit modeChanged(mode);
    }
}

int Baulicht::mode() const
{
    return d->mode;
}

void Baulicht::setPaused(bool paused)
{
    if (d->timer.isActive() == paused) {
        if (paused)
            d->timer.stop();
        else
            d->timer.start();

        emit pausedChanged(paused);
    }
}

bool Baulicht::paused() const
{
    return !d->timer.isActive();
}

QString Baulicht::addText(const QString &text, int repeat)
{
    QString path = QString("/text/%1").arg(d->lastTextId++);

    Text* object = new Text();
    object->setText(text);
    object->setRepeat(repeat);

    BaulichtExecutor e;
    d->currentText = e.convertToMorse(text);

    QDBusConnection connection = QDBusConnection::sessionBus();
    connection.registerObject(path, object, QDBusConnection::ExportAllSlots);

    d->childTexts.append(object);
    d->texts.append(path);

    return path;
}

void Baulicht::removeText(const QString &path)
{
    int pos = d->texts.indexOf(path);
    if (pos == -1) {
        qDebug() << "Unable to remove invalid path" << path;
        return;
    }

    d->texts.removeAt(pos);
    d->childTexts.removeAt(pos);
}

QStringList Baulicht::texts() const
{
    return d->texts;
}

void Baulicht::clear()
{
    d->texts.clear();
}

void Baulicht::start()
{
    setPaused(false);
}

void Baulicht::stop()
{
    setPaused(true);
}

#include "baulicht.moc"
