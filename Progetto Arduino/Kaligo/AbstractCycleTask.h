#ifndef __ABSTRACTCYCLETASK__
#define __ABSTRACTCYCLETASK__
#include "Task.h"
#include "Listeners.h"
#include "DeviceList.h"
#include "TimerTask.h"
#include "CommonSettings.h"

#define MODES 2

class AbstractCycleTask : public Task, public ReadSensorListener, public MessageListener {
public:	
	void setCycleTime(CycleMode cycle, int newTime) {
		if (this->cycleMode == cycle) {
			this->disinfectionTime = newTime;
		}
	}

	void setCycleMode(CycleMode newCycleMode) {
		this->changeMode = this->cycleMode != newCycleMode;
	}

	void setActive(bool active) {
		Task::setActive(active);
		if (active) {
			this->initCycle();
		}
	}

	bool activeNewCycle() {
		if (!this->isActive() && !this->changeMode) {
			this->setActive(true);
			return true;
		}
		return false;
	}

	void openFrontDoor() {
		if (this->isActive() && !this->isStarted) {
			this->devices->getFrontMagnet()->switchOff();
		}
	}

	void openBackDoor() {
		if (this->isActive() && !this->isStarted) {
			this->devices->getBackMagnet()->switchOff();
		}
	}

	bool addAlternativeMode(AbstractCycleTask* cycleTask) {
		if (this->cycleTaskInsert < MODES) {
			this->cycleTask[this->cycleTaskInsert++] = cycleTask;
			return true;
		}
		else {
			return false;
		}
	}

	TimerTask* getInsideTimer() {
		return this->insideTimer;
	}
protected:
	virtual void initCycle() = 0;

	AbstractCycleTask(DeviceList* devices) : AbstractCycleTask(devices, 0) { }
	
	AbstractCycleTask(DeviceList* devices, int disinfectionTime) {
		this->devices = devices;
		this->disinfectionTime = disinfectionTime;
		this->insideTimer = new TimerTask(TIMER_TASK_PERIOD);
		this->remainedTime = 0;
		this->cycleTaskInsert = 0;
		this->isStarted = false;
		this->canStart = false;
		this->changeMode = false;
	}
	
	void changeCycleMode() {
		this->setActive(false);
		for (int i = 0; i < this->cycleTaskInsert; i++) {
			if (this->cycleTask[i]->activeNewCycle()) 
				break;			
		}
	}

	void swapTime() {
		this->remainedTime = this->disinfectionTime;
	}

	TimerTask* insideTimer;
	DeviceList* devices;	
	CycleMode cycleMode;
	double remainedTime;
	bool isStarted;
	bool canStart;
	bool changeMode;

private:
	int disinfectionTime;
	int cycleTaskInsert;
	AbstractCycleTask* cycleTask[MODES];
};

#endif
