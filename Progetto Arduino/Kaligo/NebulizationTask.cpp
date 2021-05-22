#include "NebulizationTask.h"
#include "DeviceList.h"
#include "CommonSettings.h"
#include "Arduino.h"

NebulizationTask::NebulizationTask(DeviceList* deviceList) : NebulizationTask(deviceList, DEFAULT_NEBULIZATION_SECOND) { }

NebulizationTask::NebulizationTask(DeviceList* deviceList, int disinfectionTime) : AbstractCycleTask(deviceList, disinfectionTime) {
	this->cycleMode = NEBULIZATION;
}

void NebulizationTask::init(int period) {
	Task::init(period);
}

void NebulizationTask::tick() {
	int actualState = this->getActualState();

	switch (actualState) {
	case INIT:
		this->devices->getCoolingDownFan()->switchOn();
		this->devices->getUVLamp()->switchOff();
		this->devices->getFrontMagnet()->switchOff();
		this->devices->getBackMagnet()->switchOff();
		this->devices->getPump()->switchOff();
		this->devices->getBoiler()->switchOff();
		this->devices->getRGBLed()->setColor(LIGHTBLUE);
		this->setActualState(WAIT);
		break;
	case WAIT: 
		if (this->changeMode) {
			this->changeCycleMode();
		}
		else if (this->canStart && !this->isStarted) {
			this->canStart = false;
			this->setActualState(CHECK);
		}
		break;
	case CHECK: 
		if (this->predicateCheckState()) {
			this->isStarted = true;  
			this->swapTime();
			this->devices->getFrontMagnet()->switchOn();
			this->devices->getBackMagnet()->switchOn();
			this->setActualState(SATURATION_START);
		}
		else {
			this->devices->getRGBLed()->setColor(YELLOW);
		}
		break;
	case SATURATION_START:
		this->devices->getRGBLed()->setColor(WHITE); 
		this->devices->getPump()->switchOn();
		this->setActualState(SATURATION_WORKING);
		this->insideTimer->setSecond(this->remainedTime);
		this->insideTimer->start();		
		break;
	case SATURATION_WORKING:
		if (this->insideTimer->isFinishedTime()) {
			this->devices->getPump()->switchOff(); 
			this->setActualState(PARKING_START);
		}
		else if (this->devices->getThermocouple()->getValue() < THRESHOLD_WORKING) {
			this->remainedTime = this->insideTimer->stop();
			this->devices->getPump()->switchOff();			
			this->setActualState(BOILER_WARM_UP);
		}
		break;
	case BOILER_WARM_UP:
		this->devices->getBoiler()->switchOn();
		this->devices->getRGBLed()->setColor(PURPLE);
		this->setActualState(BOILER_WARM_UP);
		this->insideTimer->setSecond(DEFAULT_NEBULIZATION_WAIT_TO_WARM_UP);
		this->insideTimer->start();		
		break;
	case WAIT_BOILER_STATUS:
		if (this->insideTimer->isFinishedTime() && this->devices->getThermocouple()->getValue() > THRESHOLD_WORKING) {
			this->setActualState(SATURATION_START);
		}
		break;
	case PARKING_START:
		this->devices->getRGBLed()->setColor(BLUE);
		this->insideTimer->setSecond(DEFAULT_PARKING_SECOND);
		this->insideTimer->start();
		this->setActualState(PARKING_WORKING);
		break;
	case PARKING_WORKING:
		if (this->insideTimer->isFinishedTime()) {
			this->setActualState(FINISH_CYCLE);
		}
		break;
	case EMERGENCY:
		this->devices->getPump()->switchOff();
		this->devices->getFrontMagnet()->switchOff();
		this->devices->getBackMagnet()->switchOff();
		this->isStarted = false;
		this->devices->getRGBLed()->setColor(RED);
		this->setActualState(WAIT);
		break;
	case FINISH_CYCLE:
		this->devices->getMsgService()->sendMsg("finishCycle");
		this->devices->getRGBLed()->setColor(GREEN);
		this->isStarted = false;
		this->setActualState(WAIT);
		break;
	}
}

void NebulizationTask::notifyReadChange() {
	if (this->isStarted && this->devices->anyDoorOpen()) {
		this->stop();
	}
}

int NebulizationTask::getActualState() {
	noInterrupts();
	int actualState = this->state;
	interrupts();
	return actualState;
}

void NebulizationTask::setActualState(NebulizationState actualstate) {
	noInterrupts();
	this->state = actualstate;
	interrupts();
}

void NebulizationTask::start() {
	this->canStart = true;
}

void NebulizationTask::stop() {
	this->setActualState(EMERGENCY);
}

void NebulizationTask::initCycle() {
	this->setActualState(INIT);
}

bool NebulizationTask::predicateCheckState() {
	return this->devices->getThermocouple()->getValue() > THRESHOLD_WORKING && this->devices->allDoorClose();
}
