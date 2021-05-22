#ifndef __THERMOCOUPLEIEN__
#define __THERMOCOUPLEIEN__
#include "AnalogInput.h"
#include "CommonSettings.h"
#include <AverageThermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>

class ThermocoupleIEN : public AnalogInput {
public:
	ThermocoupleIEN(MAX6675_Thermocouple* termoCoppia);
	double getValue();
protected:
	MAX6675_Thermocouple* termoCoppia;
};
#endif
