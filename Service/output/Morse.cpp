#include "morse.h"

extern "C" {
#include "../3rdParty/BBBIOlib/BBBio_lib/BBBiolib.h"
}

void MorseOutput::setOn(bool setOn)
{
    iolib_init();
    iolib_setdir(8,12, BBBIO_DIR_OUT);

    if (setOn)
    {
        pin_high(8,12);
    }
    else
    {
        pin_low(8,12);
    }

    iolib_free();
}
