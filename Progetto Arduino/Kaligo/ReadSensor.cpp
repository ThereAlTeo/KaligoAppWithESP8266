#include "Arduino.h"
#include "ReadSensor.h"
#include "CommonSettings.h"

ReadSensor::ReadSensor(int pin, int coilSetting) : AbstractReadSensor() {
	this->pin = pin;
	this->coilSetting = coilSetting;
	pinMode(this->pin, INPUT);
	this->lastEventTime = millis();
	this->bindInterrupt(this->pin);		
}

bool ReadSensor::isActive() {
	return digitalRead(this->pin) == this->coilSetting;
}

void ReadSensor::notifyInterrupt() {
    long curr = millis();
    if (curr - this->lastEventTime > BOUNCE_TIME_READ) {
        this->lastEventTime = curr;
        for (int i = 0; i < this->nListeners; i++) {
            this->listeners[i]->notifyReadChange();
        }
    }
}
