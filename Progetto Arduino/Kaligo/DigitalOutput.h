#ifndef __DIGITALOUTPUT__
#define __DIGITALOUTPUT__

class DigitalOutput {
public:
	virtual void switchOn() = 0;
	virtual void switchOff() = 0;
};
#endif
