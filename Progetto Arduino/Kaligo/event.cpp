#include "event.h"
#include "Arduino.h"
#include "BoardSettings.h"

/* The singleton interrupt dispatcher, binding interrupts to event sources */
InterruptDispatcher interruptDispatcher;

/*
 * Functions called by the interrupt handlers, used to notify interrupts to
 * to the interrupt dispatcher
 */
void notifyInterrupt_2() { interruptDispatcher.notifyInterrupt(2); }
void notifyInterrupt_3() { interruptDispatcher.notifyInterrupt(3); }
void notifyInterrupt_18() { interruptDispatcher.notifyInterrupt(18); }
void notifyInterrupt_19() { interruptDispatcher.notifyInterrupt(19); }
void notifyInterrupt_20() { interruptDispatcher.notifyInterrupt(20); }
void notifyInterrupt_21() { interruptDispatcher.notifyInterrupt(21); }

InterruptDispatcher::InterruptDispatcher() {
    notifyFunctions[0] = notifyInterrupt_2;
    notifyFunctions[1] = notifyInterrupt_3;
    notifyFunctions[2] = notifyInterrupt_18;
    notifyFunctions[3] = notifyInterrupt_19;
    notifyFunctions[4] = notifyInterrupt_20;
    notifyFunctions[5] = notifyInterrupt_21;   
}

void InterruptDispatcher::bind(int pin, EventSource* src) {
    if (interruptPinBoardAvailable(pin)) {
        int index = convertPinToArrayIndex(pin);
        if (index > -1) {
            sourceRegisteredOnPin[index] = src;
            attachInterrupt(digitalPinToInterrupt(pin), notifyFunctions[index], CHANGE);
        }       
    }    
}

void InterruptDispatcher::notifyInterrupt(int pin) {
    if (interruptPinBoardAvailable(pin)) {
        int index = convertPinToArrayIndex(pin);
        if (index > -1) {
            sourceRegisteredOnPin[pin]->notifyInterrupt();
        }        
    }    
}

/* ------------------- EventSource ----------------- */
void EventSource::bindInterrupt(int pin) {
    interruptDispatcher.bind(pin, this);
}
