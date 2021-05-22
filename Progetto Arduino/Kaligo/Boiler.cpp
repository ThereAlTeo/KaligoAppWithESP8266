#include "Boiler.h"
#include "Arduino.h"

Boiler::Boiler(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Boiler::switchOn() {
	digitalWrite(this->pin, LOW);
}

void Boiler::switchOff() {
	digitalWrite(this->pin, HIGH);
}
