#ifndef ONOFF_GPIO_H
#define ONOFF_GPIO_H

#include "morse.h"
#include "../gpiopin.h"

#include <QFile>

class OnOffMorse : public MorseOutput
{
public:
    OnOffMorse(int pin);
    ~OnOffMorse();

    // MorseOutput interface
    void setOn(bool on);

protected:
    GPIOPin pin;
};

#endif // ONOFF_GPIO_H
