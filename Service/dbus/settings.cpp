#include "settings.h"

#include <QSettings>

class Settings::Private
{
public:
    QSettings settings;
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
    if (dit() != milliseconds) {
        d->settings.setValue("dit", milliseconds);
        emit ditChanged(milliseconds);
    }
}

int Settings::dit() const
{
    return d->settings.value("dit", 200).toInt();
}

void Settings::setTextSpacing(int milliseconds)
{
    if (textSpacing() != milliseconds) {
        d->settings.setValue("textSpacing", milliseconds);
        emit textSpacingChanged(milliseconds);
    }
}

int Settings::textSpacing() const
{
    return d->settings.value("textSpacing", dit()*10).toInt();
}

void Settings::setPin(int pinNumber)
{
    if (pin() != pinNumber) {
        d->settings.setValue("pin", pinNumber);
        emit pinChanged(pinNumber);
    }
}

int Settings::pin() const
{
    return d->settings.value("pin", 17).toInt();
}
