#ifndef __LISTENERS__
#define __LISTENERS__
#include "CommonSettings.h"

/*
 * Interface of listeners that are notified
 * when a readSensor generate an event
 */
class ReadSensorListener {
public:
    virtual void notifyReadChange() = 0;
};

/*
 * Interface of listeners that are notified
 * when a Bluetooth device recieve  new message
 */
class MessageListener {
public:
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void setCycleTime(CycleMode cycle, int newTime) = 0;
    virtual void setCycleMode(CycleMode newCycleMode) = 0;
    virtual void openFrontDoor() = 0;
    virtual void openBackDoor() = 0;
};

#endif 
