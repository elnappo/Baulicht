#include "baulicht.h"
#include "blink.h"
#include "text.h"
#include "baulichtexecutor.h"
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
    : mode(0)
    , paused(true)
    , currentPosition(0)
    {
        connect(&timer, SIGNAL(timeout()), this, SLOT(timeout()));
        timer.setInterval(300);
    }

    // Properties
    int mode;
    bool paused;
    QStringList texts;

    QString currentText;
    int currentPosition;

    QTimer timer;
    QList<Text*> childTexts;

    OnOffMorse morse;

public slots:
    void onPauseChanged();
    void timeout();
};

void Baulicht::Private::onPauseChanged()
{
    timer.start();
}

void Baulicht::Private::timeout()
{
    const QChar c = currentText.at(currentPosition);
    bool on = (c == '=');

    qDebug() << (on ? "on" : "off");
    morse.setOn(on);

    currentPosition = ++currentPosition % currentText.length();

    if (currentPosition == 0)
        qDebug() << "-----------------------";
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
    if (d->paused != paused) {
        d->paused = paused;
        emit pausedChanged(paused);
    }
}

bool Baulicht::paused() const
{
    return d->paused;
}

QString Baulicht::addText(const QString &text, int interval, int repeat)
{
    QString path = QString("/text/%1").arg(d->texts.size());

    Text* object = new Text();
    object->setText(text);
    object->setInterval(interval);
    object->setRepeat(repeat);

    BaulichtExecutor e;
    d->currentText = e.convertToMorse(text);

    QDBusConnection connection = QDBusConnection::systemBus();
    connection.registerObject(path, object, QDBusConnection::ExportAllSlots);

    d->childTexts.append(object);
    d->texts.append(path);

    return path;
}

void Baulicht::removeText(const QString &path)
{
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
