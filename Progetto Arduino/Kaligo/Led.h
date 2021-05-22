#ifndef __LED__
#define __LED__

#include "DigitalOutput.h"

class Led : public DigitalOutput {
public:
    Led(int pin);
    void switchOn();
    void switchOff();
private:
    int pin;
};

#endif