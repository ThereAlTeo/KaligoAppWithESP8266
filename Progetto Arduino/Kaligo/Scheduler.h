#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Task.h"

#define MAX_TASKS 15

class Scheduler {

    int basePeriod;
    int nTasks;
    Task* taskList[MAX_TASKS];

public:
    void init(int basePeriod);
    void reset(int basePeriod);
    virtual bool addTask(Task* task);
    virtual void schedule();
    virtual void removeTasks();
};

#endif

