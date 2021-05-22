#include "DeviceList.h"
#include "RGBLed.h"
#include "Fan.h"
#include "Pump.h"
#include "Magnet.h"
#include "UVLamp.h"
#include "ReadSensor.h"
#include "Boiler.h"
#include "ThermocoupleIEN.h"
#include "MsgService.h"
#include "CommonSettings.h"
#include "Arduino.h"

DeviceList::DeviceList(MAX6675_Thermocouple* termoCoppia) {
	this->rgbLed = new RGBLed(RED_CHANNEL_LED, BLUE_CHANNEL_LED, GREEN_CHANNEL_LED);
	this->coolingDownFan = new Fan(COOLING_DOWN_FAN_PIN);
	this->pump = new Pump(BOILER_PUMP_PIN);
	this->frontMagnet = new Magnet(FRONT_MAGNET_PIN);
	this->backMagnet = new Magnet(BACK_MAGNET_PIN);
	this->uvLamp = new UVLamp(UVLAMP_PIN);
	this->readFrontDoor = new ReadSensor(FRONT_DOOR_READ_PIN, HIGH);
	this->readBackDoor = new ReadSensor(BACK_DOOR_READ_PIN, HIGH);
	this->boiler = new Boiler(BOILER_PIN);
	this->myThermocouple = new ThermocoupleIEN(termoCoppia);
	this->msgService = new MsgService(BLUETOOTH_RX, BLUETOOTH_TX);
	this->msgService->init();
}

RGBLed* DeviceList::getRGBLed() {
	return this->rgbLed;
}

Fan* DeviceList::getCoolingDownFan() {
	return this->coolingDownFan;
}

Pump* DeviceList::getPump() {
	return this->pump;
}

Magnet* DeviceList::getFrontMagnet() {
	return this->frontMagnet;
}

Magnet* DeviceList::getBackMagnet() {
	return this->backMagnet;
}

UVLamp* DeviceList::getUVLamp() {
	return this->uvLamp;
}

ReadSensor* DeviceList::getReadFrontDoor() {
	return this->readFrontDoor;
}

ReadSensor* DeviceList::getReadBackDoor() {
	return this->readBackDoor;
}

Boiler* DeviceList::getBoiler() {
	return this->boiler;
}

ThermocoupleIEN* DeviceList::getThermocouple() {
	return this->myThermocouple;
}

MsgService* DeviceList::getMsgService() {
	return this->msgService;
}

bool DeviceList::allDoorClose() {
	return this->readFrontDoor->isActive() && this->readBackDoor->isActive();
}

bool DeviceList::anyDoorOpen() {
	return !this->allDoorClose();
}
