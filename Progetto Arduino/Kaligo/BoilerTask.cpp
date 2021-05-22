#include "BoilerTask.h"
#include "Arduino.h"
#include "ThermocoupleIEN.h"
#include "CommonSettings.h"

BoilerTask::BoilerTask(DeviceList* deviceList) {
	this->devices = deviceList;	
}

void BoilerTask::init(int period) {
	Task::init(period);
}

void BoilerTask::setActive(bool active) {
	Task::setActive(active);
}

void BoilerTask::tick() {
	if (this->devices->getThermocouple()->getValue() >= THRESHOLD_SUP) {
		this->devices->getBoiler()->switchOff();
	}

	if (this->devices->getThermocouple()->getValue() <= THRESHOLD_INF) {
		this->devices->getBoiler()->switchOn();
	}
}
