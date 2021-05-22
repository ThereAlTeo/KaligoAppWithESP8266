#include "ThermocoupleIEN.h"
#include "Arduino.h"
#include <AverageThermocouple.h>
#include <MAX6675_Thermocouple.h>
#include <SmoothThermocouple.h>
#include <Thermocouple.h>

ThermocoupleIEN::ThermocoupleIEN(MAX6675_Thermocouple* termoCoppia) {
	this->termoCoppia = termoCoppia;
}

double ThermocoupleIEN::getValue() {
	return this->termoCoppia->readCelsius();
}
