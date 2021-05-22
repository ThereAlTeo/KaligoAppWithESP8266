#ifndef __BOILERTASK__
#define __BOILERTASK__

#include "Task.h"
#include "DeviceList.h"

class BoilerTask : public Task {

public:
	BoilerTask(DeviceList* deviceList);
	void init(int period);
	void setActive(bool active);
	void tick();

private:
	DeviceList* devices;
};

#endif
