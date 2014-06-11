#include "onoff_gpio.h"

extern "C" {
#include "../3rdParty/BBBIOlib/BBBio_lib/BBBiolib.h"
}

typedef void (*PinFunction)(char port, char pin);

PinFunction pinMap[2] = {
    pin_high,
    pin_low
};


OnOffMorse::OnOffMorse()
{
    iolib_init();
    iolib_setdir(8,12, BBBIO_DIR_OUT);
}

OnOffMorse::~OnOffMorse()
{
    iolib_free();
}

void OnOffMorse::setOn(bool setOn)
{
    pinMap[setOn ? 0 : 1](8, 12);
}
