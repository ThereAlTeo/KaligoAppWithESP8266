#ifndef __TASK__
#define __TASK__

class Task {
private:		
	int timeElapsed;
	int myPeriod;
	bool active;

public:
	Task() : Task(0, true) { }
	
	Task(int period, bool active) {
		this->active = active;
		this->timeElapsed = 0;
		this->myPeriod = period;
	}

	virtual void init(int period) {
		this->myPeriod = period;
		this->timeElapsed = 0;
		this->setActive(true);
	}

	virtual void tick() = 0;

	bool updateAndCheckTime(int basePeriod) {
		this->timeElapsed += basePeriod;
		if (this->timeElapsed >= this->myPeriod) {
			this->timeElapsed = 0;
			return true;
		}
		else {
			return false;
		}
	}

	bool isActive() {
		return this->active;
	}

	void setActive(bool active) {
		this->timeElapsed = 0;
		this->active = active;
	}
};

#endif
