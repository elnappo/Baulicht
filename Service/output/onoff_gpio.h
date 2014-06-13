#ifndef ONOFF_GPIO_H
#define ONOFF_GPIO_H

#include "morse.h"

#include <QFile>

class OnOffMorse : public MorseOutput
{
public:
    OnOffMorse();
    ~OnOffMorse();

    // MorseOutput interface
    void setOn(bool on);

protected:
    void exportPin(int pin);
    void setDirection(int pin, const QByteArray& direction);

protected:
    QFile m_file;
};

#endif // ONOFF_GPIO_H
