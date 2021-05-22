#ifndef __DEVICELIST__
#define __DEVICELIST__
#include "RGBLed.h"
#include "Fan.h"
#include "Pump.h"
#include "Magnet.h"
#include "UVLamp.h"
#include "ReadSensor.h"
#include "Boiler.h"
#include "ThermocoupleIEN.h"
#include "MsgService.h"

class DeviceList {
public:
	DeviceList(MAX6675_Thermocouple* termoCoppia);
	RGBLed* getRGBLed();
	Fan* getCoolingDownFan();
	Pump* getPump();
	Magnet* getFrontMagnet();
	Magnet* getBackMagnet();
	UVLamp* getUVLamp();
	ReadSensor* getReadFrontDoor();
	ReadSensor* getReadBackDoor();
	Boiler* getBoiler();
	ThermocoupleIEN* getThermocouple();
	MsgService* getMsgService();

	bool allDoorClose();
	bool anyDoorOpen();

private:
	RGBLed* rgbLed;
	Fan* coolingDownFan;
	Pump* pump;
	Magnet* frontMagnet;
	Magnet* backMagnet;
	UVLamp* uvLamp;
	ReadSensor* readFrontDoor;
	ReadSensor* readBackDoor;
	Boiler* boiler;
	ThermocoupleIEN* myThermocouple;
	MsgService* msgService;
};
#endif
