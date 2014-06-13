#include "onoff_gpio.h"

#include <QDebug>

OnOffMorse::OnOffMorse()
{
    int pin = 17;
    exportPin(pin);
    setDirection(pin, "out");

    QString path = QString("/sys/class/gpio/gpio%1/value").arg(pin);
    m_file.setFileName(path);
    if (!m_file.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open pin value setter:" << m_file.errorString();
    }
}

OnOffMorse::~OnOffMorse()
{
}

void OnOffMorse::setOn(bool setOn)
{
    m_file.write(setOn ? "1" : "0");
}

void OnOffMorse::exportPin(int pin)
{
    QString path = QString("/sys/class/gpio/export");
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write( QString::number(pin).toLatin1() );
    } else {
        qDebug() << "Failed to export pin:" << file.errorString();
    }
}

void OnOffMorse::setDirection(int pin, const QByteArray &direction)
{
    QString path = QString("/sys/class/gpio/gpio%1/direction").arg(pin);
    QFile file(path);
    if (file.open(QIODevice::WriteOnly)) {
        file.write(direction);
    } else {
        qDebug() << "Failed to set value on pin:" << file.errorString();
    }
}
