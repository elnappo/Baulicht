#ifndef MORSEOUTPUT_H
#define MORSEOUTPUT_H

#include "output.h"

class MorseOutput : public Output
{
public:
    virtual void setOn(bool on) = 0;
};

#endif // MORSEOUTPUT_H
