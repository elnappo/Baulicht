#include "baulicht.h"

class Baulicht::Private
{
public:
    Private()
    : mode(0)
    , paused(false)
    {
    }

    // Properties
    int mode;
    bool paused;
    QStringList texts;
};

Baulicht::Baulicht(QObject *parent)
: QObject(parent)
, d(new Private)
{
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
    return QString();
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
