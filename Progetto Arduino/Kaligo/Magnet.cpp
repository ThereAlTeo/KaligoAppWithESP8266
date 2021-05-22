#include "Magnet.h"
#include "Arduino.h"

Magnet::Magnet(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void Magnet::switchOn() {
	digitalWrite(this->pin, LOW);
}

void Magnet::switchOff() {
	digitalWrite(this->pin, HIGH);
}

bool Magnet::isActive() {
	return digitalRead(this->pin) == LOW;
}
