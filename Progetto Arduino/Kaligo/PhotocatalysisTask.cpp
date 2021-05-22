#include "PhotocatalysisTask.h"

PhotocatalysisTask::PhotocatalysisTask(DeviceList* deviceList) : AbstractCycleTask(deviceList, DEFAULT_FOTOCATALISI_SECOND) {
	this->cycleMode = PHOTOCATALYSIS;
}

void PhotocatalysisTask::notifyReadChange() {
	if (this->isStarted && this->devices->anyDoorOpen()) {
		this->stop();
	}
}

void PhotocatalysisTask::init(int period) {
	Task::init(period);
}

void PhotocatalysisTask::tick() {
	int actualState = this->getActualState();

	switch (actualState) {
	case INIT:
		this->devices->getCoolingDownFan()->switchOn();
		this->devices->getUVLamp()->switchOff();
		this->devices->getFrontMagnet()->switchOff();
		this->devices->getBackMagnet()->switchOff();
		this->devices->getPump()->switchOff();
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
		if (this->devices->allDoorClose()) {
			this->isStarted = true;
			this->swapTime();
			this->devices->getFrontMagnet()->switchOn();
			this->devices->getBackMagnet()->switchOn();
			this->setActualState(PHOTOCATALYSIS_START);
		}
		else {
			this->devices->getRGBLed()->setColor(YELLOW);
		}
		break;
	case PHOTOCATALYSIS_START:
		this->devices->getRGBLed()->setColor(BLUE);
		this->devices->getUVLamp()->switchOn();
		this->setActualState(PHOTOCATALYSIS_WORKING);
		this->insideTimer->setSecond(this->remainedTime);
		this->insideTimer->start();
		break;
	case PHOTOCATALYSIS_WORKING:
		if (this->insideTimer->isFinishedTime()) {
			this->devices->getUVLamp()->switchOff();
			this->setActualState(FINISH_CYCLE);
		}
		break;
	case EMERGENCY:
		this->devices->getUVLamp()->switchOff();
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

int PhotocatalysisTask::getActualState() {
	noInterrupts();
	int actualState = this->state;
	interrupts();
	return actualState;
}

void PhotocatalysisTask::setActualState(PhotocatalysisState actualstate) {
	noInterrupts();
	this->state = actualstate;
	interrupts();
}

void PhotocatalysisTask::start() {
	this->canStart = true;
}

void PhotocatalysisTask::stop() {
	this->setActualState(EMERGENCY);
}

void PhotocatalysisTask::initCycle() {
	this->setActualState(INIT);
}
