#ifndef __BOILER__
#define __BOILER__
#include "DigitalOutput.h"

class Boiler : public DigitalOutput {
public:
	Boiler(int pin);
	void switchOn();
	void switchOff();
protected:
	int pin;
};
#endif 