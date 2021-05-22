#ifndef __PUMP__
#define __PUMP__
#include "DigitalOutput.h"

class Pump : public DigitalOutput {
public:
	Pump(int pin);
	void switchOn();
	void switchOff();
protected:
	int pin;
};
#endif

