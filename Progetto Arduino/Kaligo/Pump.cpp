#include "Pump.h"
#include "Arduino.h"

Pump::Pump(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Pump::switchOn() {
	digitalWrite(this->pin, LOW);
}

void Pump::switchOff() {
	digitalWrite(this->pin, HIGH);
}
