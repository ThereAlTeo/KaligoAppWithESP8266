#ifndef __NIGHTMODETASK__
#define __NIGHTMODETASK__
#include "NebulizationTask.h"
#include "DeviceList.h"

class NightModeTask : public NebulizationTask {
public:
	NightModeTask(DeviceList* deviceList);
	void notifyReadChange();
protected:
	bool predicateCheckState();
};

#endif 
