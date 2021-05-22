#include "Fan.h"
#include "Arduino.h"

Fan::Fan(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Fan::switchOn() {
	digitalWrite(this->pin, LOW);
}

void Fan::switchOff() {
	digitalWrite(this->pin, HIGH);
}
