#ifndef __BLUETOOTHTASK__
#define __BLUETOOTHTASK__
#include "AbstractComunicationTask.h"
#include "DeviceList.h"

class BluetoothTask : public AbstractComunicationTask {
public:
	BluetoothTask(MsgService* msgService);
	void tick();
	void init(int period);
	void startNotify();
	void stopNotify();
	void setCycleTimeNotify(CycleMode cycle, int newTime);
	void setCycleModeNotify(CycleMode newCycleMode);
	void openFrontDoorNotify();
	void openBackDoorNotify();
private:
	void handleMessage(String command, String value);
	MsgService* msgService;
};

#endif

