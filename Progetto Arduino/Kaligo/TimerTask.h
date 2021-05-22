#ifndef __TIMERTASK__
#define __TIMERTASK__

#include "Task.h"
#include "CommonSettings.h"

class TimerTask : public Task {

public:
	TimerTask(int period);
	void tick();
	void start();
	double stop();
	void setSecond(double second);
	void setAction(void (*proc)(void));
	bool isFinishedTime();

private:
	double second;
	unsigned long startTimer;
	bool isFinished;
	void (*proc)(void);
};

#endif
