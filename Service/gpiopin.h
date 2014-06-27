#ifndef GPIOPIN_H
#define GPIOPIN_H

#include <QString>

class GPIOPin
{
public:
    GPIOPin(int pin);
    ~GPIOPin();

    enum Direction
    {
        Unknown,
        In,
        Out
    };

    Direction direction() const;
    void setDirection(const Direction &direction);

    QByteArray value() const;
    void setValue(const QByteArray& value);

    bool isValid() const;

    int pin() const;
    QString errorString() const;

protected:
    class Private;
    Private *d;
};

#endif // GPIOPIN_H
