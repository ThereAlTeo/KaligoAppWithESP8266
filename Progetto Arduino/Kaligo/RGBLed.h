#ifndef __RGBLED__
#define __RGBLED__

#include "DigitalOutput.h"
#include "Led.h"
#include "CommonSettings.h"

class RGBLed : public DigitalOutput {
public:
    RGBLed(int redChannel, int blueChannel, int greenChannel);
    void switchOn();
    void switchOff();
    void setColor(Color color);
private:
    Led* redChannel;
    Led* blueChannel;
    Led* greenChannel;
    Color color;
};

#endif