#ifndef __NEBULIZATIONTASK__
#define __NEBULIZATIONTASK__
#include "AbstractCycleTask.h"

class NebulizationTask : public AbstractCycleTask {
public:
	NebulizationTask(DeviceList* deviceList);
	void notifyReadChange();
	void start();
	void stop();
	void init(int period);
	void tick();
protected:
	NebulizationTask(DeviceList* deviceList, int disinfectionTime);
	enum NebulizationState { INIT, WAIT, CHECK, SATURATION_START, SATURATION_WORKING, BOILER_WARM_UP, WAIT_BOILER_STATUS, 
		   PARKING_START, PARKING_WORKING, EMERGENCY, FINISH_CYCLE } state;
	
	void setActualState(NebulizationState actualstate);
	int getActualState();
	void initCycle();
	bool predicateCheckState();	
};

#endif 
