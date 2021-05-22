#ifndef __MINI_TIMER_1_H__
#define __MINI_TIMER_1_H__

#include "Arduino.h"

class MiniTimerOne {
public:
    static MiniTimerOne* getInstance();
    void init(void);
    void setPeriod(unsigned long int period);
    void attachInterrupt(void (*isr)(void));
    void detachInterrupt(void);
    void start(void);
    void stop(void);
    void reset(void);
    void (*getCallback(void))(void);
private:
    static MiniTimerOne* SINGLETON;

    MiniTimerOne(void);

    void (*_isrCallback)(void);
    char _clockSelectBits;
};
extern MiniTimerOne SchedulerTimer;

#endif
