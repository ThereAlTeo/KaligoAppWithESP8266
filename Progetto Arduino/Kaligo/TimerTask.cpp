#include "TimerTask.h"
#include "CommonSettings.h"
#include "Arduino.h"

#define MILLIS_TO_SECOND 1000

TimerTask::TimerTask(int period) : Task(period, false) {
	this->second = 0;
	this->startTimer = 0;
	this->isFinished = false;
	this->proc = emptyFunction;
}

void TimerTask::tick() {
	if (this->isActive() && !this->isFinished && (millis() - this->startTimer) >= this->second * MILLIS_TO_SECOND) {
		this->stop();
		if (this->proc != NULL) {
			this->proc();
		}		
	}
}

void TimerTask::start() {
	this->setActive(true);
	this->isFinished = false;
	this->startTimer = millis();
}

double TimerTask::stop() {
	this->setActive(false);
	this->isFinished = true;
	return (millis() - this->startTimer) / MILLIS_TO_SECOND;
}

void TimerTask::setSecond(double second) {
	this->second = second;
}

void TimerTask::setAction(void (*proc)(void)) {
	this->proc = proc;
}

bool TimerTask::isFinishedTime() {
	return this->isFinished;
}
