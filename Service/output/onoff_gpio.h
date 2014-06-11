#ifndef ONOFF_GPIO_H
#define ONOFF_GPIO_H

#include "morse.h"
#include "stdio.h"

static FILE *fp;

class OnOffMorse : public MorseOutput
{
public:
    OnOffMorse();
    ~OnOffMorse();

    // MorseOutput interface
    void setOn(bool on);
};

#endif // ONOFF_GPIO_H
