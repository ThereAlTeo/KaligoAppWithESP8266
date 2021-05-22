#ifndef __MAGNET__
#define __MAGNET__
#include "DigitalOutput.h"

class Magnet : public DigitalOutput {
public:
	Magnet(int pin);
	void switchOn();
	void switchOff();
	bool isActive();
protected:
	int pin;
};
#endif
