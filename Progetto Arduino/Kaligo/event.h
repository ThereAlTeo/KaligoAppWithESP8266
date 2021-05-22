#ifndef __EVENT__
#define __EVENT__
#include "CommonSettings.h"
#include "BoardSettings.h"

/**
 * Base class representing an event source
 */
class EventSource {
public:
    /* called by the interrupt dispatcher to notify a new event */
    virtual void notifyInterrupt() = 0;

protected:
    void bindInterrupt(int pin);
};

/**
 * Base class representing an event source
 */
class MessageEventSource {
public:
    virtual void startNotify() = 0;
    virtual void stopNotify() = 0;
    virtual void setCycleTimeNotify(CycleMode cycle, int newTime) = 0;
    virtual void setCycleModeNotify(CycleMode newCycleMode) = 0;
    virtual void openFrontDoorNotify() = 0;
    virtual void openBackDoorNotify() = 0;
};

/**
 * Class binding interrupts to event sources
 */
class InterruptDispatcher {
public:
    InterruptDispatcher();

    /* to bind an event source to a specific pin */
    void bind(int pin, EventSource* src);

    /* called by interrupt handlers */
    void notifyInterrupt(int pin);
private:
    EventSource* sourceRegisteredOnPin[NUM_PINS_AVAILABLE];
    void (*notifyFunctions[NUM_PINS_AVAILABLE])() = {};
};

#endif
