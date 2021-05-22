#ifndef __UVLAMP__
#define __UVLAMP__
#include "DigitalOutput.h"

class UVLamp : public DigitalOutput {
public:
	UVLamp(int pin);
	void switchOn();
	void switchOff();
protected:
	int pin;
};
#endif

