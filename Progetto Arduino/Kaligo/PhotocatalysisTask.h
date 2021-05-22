#ifndef __PHOTOCATALYSISTASK__
#define __PHOTOCATALYSISTASK__
#include "AbstractCycleTask.h"

class PhotocatalysisTask : public AbstractCycleTask {
public:
	PhotocatalysisTask(DeviceList* deviceList);
	void notifyReadChange();
	void start();
	void stop();
	void init(int period);
	void tick();
protected:
	enum PhotocatalysisState {
		INIT, WAIT, CHECK, PHOTOCATALYSIS_START, PHOTOCATALYSIS_WORKING, EMERGENCY, FINISH_CYCLE
	} state;

	void setActualState(PhotocatalysisState actualstate);
	int getActualState();
	void initCycle();
};
#endif 
