#include "onoff_gpio.h"

#include <QDebug>

OnOffMorse::OnOffMorse(int pinNumber)
: pin(pinNumber)
{
    pin.setDirection(GPIOPin::Out);
}

OnOffMorse::~OnOffMorse()
{
}

void OnOffMorse::setOn(bool setOn)
{
    pin.setValue(setOn ? "1" : "0");
}
