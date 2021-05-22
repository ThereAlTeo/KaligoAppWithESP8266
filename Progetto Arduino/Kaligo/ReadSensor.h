#ifndef __READSENSOR__
#define __READSENSOR__
#include "DigitalInput.h"
#include "event.h"
#include "Listeners.h"

#define MAX_READ_LISTENERS 5

/*
 * The base class for buttons generating events
 */
class AbstractReadSensor : public EventSource, public DigitalInput {
public:
    /* to add a new listener */
    bool addListener(ReadSensorListener* listener) {
        if (nListeners < MAX_READ_LISTENERS) {
            this->listeners[nListeners++] = listener;
            return true;
        }
        else {
            return false;
        }
    }
protected:
    AbstractReadSensor() {
        this->nListeners = 0;
    }

    int nListeners;
    ReadSensorListener* listeners[MAX_READ_LISTENERS];
};

class ReadSensor : public AbstractReadSensor {
public:
	ReadSensor(int pin, int coilSetting);
	bool isActive();
protected:
    void notifyInterrupt();
    int lastEventTime;
	int pin;
	int coilSetting;
};

#endif
