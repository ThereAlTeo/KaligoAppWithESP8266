#include "NightModeTask.h"

NightModeTask::NightModeTask(DeviceList* deviceList) : NebulizationTask(deviceList, DEFAULT_NIGHT_SECOND) {
	this->cycleMode = NIGHT_MODE;
}

bool NightModeTask::predicateCheckState() {
	return this->devices->getThermocouple()->getValue() > THRESHOLD_WORKING && this->devices->anyDoorOpen();
}


void NightModeTask::notifyReadChange() {
	if (this->isStarted && this->devices->allDoorClose()) {
		this->stop();
	}
}