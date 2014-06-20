#include "settings.h"

class Settings::Private
{
public:
    Private()
    : dit(200)
    , textSpacing(dit*10)
    {
    }

    int dit;
    int textSpacing;
};


Settings::Settings(QObject *parent)
: QObject(parent)
, d(new Private)
{
}

Settings::~Settings()
{
    delete d;
}

void Settings::setDit(int milliseconds)
{
    if (d->dit != milliseconds) {
        d->dit = milliseconds;
        emit ditChanged(milliseconds);
    }
}

int Settings::dit() const
{
    return d->dit;
}

void Settings::setTextSpacing(int milliseconds)
{
    if (d->textSpacing != milliseconds) {
        d->textSpacing = milliseconds;
        emit textSpacingChanged(milliseconds);
    }
}

int Settings::textSpacing() const
{
    return d->textSpacing;
}
