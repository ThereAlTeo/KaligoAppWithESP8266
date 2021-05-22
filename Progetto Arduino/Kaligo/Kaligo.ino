#include "Scheduler.h"
#include "Arduino.h"
#include "CommonSettings.h"
#include "DeviceList.h"
#include "MsgService.h"
#include "BluetoothTask.h"
#include "NebulizationTask.h"
#include "NightModeTask.h"
#include "PhotocatalysisTask.h"
#include "BoilerTask.h"

Scheduler scheduler;

// the setup function runs once when you press reset or power the board
void(*resetFunc) (void) = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(9600);
	while (!Serial) {}
	Serial.println("READY");
	scheduler.init(SCHEDULER_PERIOD);

	MAX6675_Thermocouple thermocouple = MAX6675_Thermocouple(SCK_PIN, CS_PIN, SO_PIN);
	DeviceList* device = new DeviceList(&thermocouple);

	BoilerTask* boilerTask = new BoilerTask(device);
	boilerTask->init(BOILER_PERDIOD);

	BluetoothTask* bluetoothTask = new BluetoothTask(device->getMsgService());
	bluetoothTask->init(COMUNICATION_PERIOD);

	NebulizationTask* nebulizationTask = new NebulizationTask(device);
	nebulizationTask->init(NEBULIZATION_PERIOD);

	NightModeTask* nightModeTask = new NightModeTask(device);
	nightModeTask->init(NIGHTMODE_PERIOD);
	nightModeTask->setActive(false);

	PhotocatalysisTask* photocatalysisTask = new PhotocatalysisTask(device);
	photocatalysisTask->init(PHOTOCATALYSIS_PERIOD);
	photocatalysisTask->setActive(false);

	nebulizationTask->addAlternativeMode(nightModeTask);
	nebulizationTask->addAlternativeMode(photocatalysisTask);

	nightModeTask->addAlternativeMode(nebulizationTask);
	nightModeTask->addAlternativeMode(photocatalysisTask);

	photocatalysisTask->addAlternativeMode(nightModeTask);
	photocatalysisTask->addAlternativeMode(nebulizationTask);

	device->getReadFrontDoor()->addListener(nebulizationTask);
	device->getReadFrontDoor()->addListener(nightModeTask);
	device->getReadFrontDoor()->addListener(photocatalysisTask);

	device->getReadBackDoor()->addListener(nebulizationTask);
	device->getReadBackDoor()->addListener(nightModeTask);
	device->getReadBackDoor()->addListener(photocatalysisTask);

	bluetoothTask->addListener(nebulizationTask);
	bluetoothTask->addListener(nightModeTask);
	bluetoothTask->addListener(photocatalysisTask);

	scheduler.addTask(boilerTask);
	scheduler.addTask(bluetoothTask);
	scheduler.addTask(nebulizationTask);
	scheduler.addTask(nightModeTask);
	scheduler.addTask(photocatalysisTask);
	scheduler.addTask(nebulizationTask->getInsideTimer());
	scheduler.addTask(nightModeTask->getInsideTimer());
	scheduler.addTask(photocatalysisTask->getInsideTimer());
}

// the loop function runs over and over again until power down or reset
void loop() {
	scheduler.schedule();
}

void resetApplication() {
	resetFunc();
}

void emptyFunction() { }
