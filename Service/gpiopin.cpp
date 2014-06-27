#include "gpiopin.h"

#include <QFile>
#include <QDebug>

namespace {
    static const QString exportPath = "/sys/class/gpio/export";
    static const QString pinPath = "/sys/class/gpio/gpio%1";
    static const QString valuePath = "/sys/class/gpio/gpio%1/value";
    static const QString directionPath = "/sys/class/gpio/gpio%1/direction";
}

class GPIOPin::Private
{
public:
    // Properties
    int pin;
    QString errorString;

    // Functions
    bool tryExport();
};

bool GPIOPin::Private::tryExport()
{
    errorString.clear();

    QString path = pinPath.arg(pin);
    if (QFile::exists(path))
        return true;

    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QString::number(pin).toLatin1());
        return true;
    } else {
        errorString = file.errorString();
    }

    return false;
}


GPIOPin::GPIOPin(int pin)
: d(new Private)
{
    d->pin = pin;
}

GPIOPin::~GPIOPin()
{
    delete d;
}

GPIOPin::Direction GPIOPin::direction() const
{
    d->tryExport();
    d->errorString.clear();

    QString path = directionPath.arg(d->pin);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray direction = file.readAll().trimmed();
        if (direction == "in")
            return In;
        else if (direction == "out")
            return Out;
    } else {
        d->errorString = file.errorString();
    }

    return Unknown;
}

void GPIOPin::setDirection(const Direction &direction)
{
    d->tryExport();
    d->errorString.clear();

    QString path = directionPath.arg(d->pin);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        switch(direction) {
        case In:
            file.write("in");
            break;

        case Out:
            file.write("out");
            break;

        default:
            break;
        }
    } else {
        qDebug() << "Failed to set direction on pin:" << file.errorString();
        d->errorString = file.errorString();
    }
}

QByteArray GPIOPin::value() const
{
    d->tryExport();
    d->errorString.clear();

    QString path = valuePath.arg(d->pin);
    QFile file(path);
    if (file.open(QIODevice::ReadOnly)) {
        return file.readAll();
    } else {
        d->errorString = file.errorString();
    }

    return QByteArray();
}

void GPIOPin::setValue(const QByteArray &value)
{
    d->tryExport();
    d->errorString.clear();

    QString path = valuePath.arg(d->pin);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(value);
    } else {
        qDebug() << "Failed to set value on pin:" << file.errorString();
        d->errorString = file.errorString();
    }
}

int GPIOPin::pin() const
{
    return d->pin;
}

QString GPIOPin::errorString() const
{
    return d->errorString;
}
