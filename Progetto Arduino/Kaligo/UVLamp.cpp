#include "UVLamp.h"
#include "Arduino.h"

UVLamp::UVLamp(int pin) {
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
}

void UVLamp::switchOn() {
	digitalWrite(this->pin, LOW);
}

void UVLamp::switchOff() {
	digitalWrite(this->pin, HIGH);
}
