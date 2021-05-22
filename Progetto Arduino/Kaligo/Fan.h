#ifndef __FAN__
#define __FAN__
#include "DigitalOutput.h"

class Fan : public DigitalOutput {
public:
	Fan(int pin);
	void switchOn();
	void switchOff();
protected:
	int pin;
};
#endif

