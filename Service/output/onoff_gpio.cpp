#include "onoff_gpio.h"
#include <stdlib.h>

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
    if ((fp = fopen("/sys/class/gpio/export", "w")) == NULL){
        printf("Cannot open export file.\n");
        exit(1);
    }
    fprintf( fp, "%d", 30 );
    fclose(fp);

    if ((fp = fopen("/sys/class/gpio/gpio30/direction", "rb+")) == NULL){
        printf("Cannot open direction file.\n");
        exit(1);
    }
    fprintf(fp, "high");
    fclose(fp);

    if ((fp = fopen("/sys/class/gpio/gpio30/value", "rb+")) == NULL){
        printf("Cannot open value file.\n");
        exit(1);
    }
}

OnOffMorse::~OnOffMorse()
{
    fclose(fp);
}

void OnOffMorse::setOn(bool setOn)
{
    fprintf(fp, setOn ? "1" : "0");
}
