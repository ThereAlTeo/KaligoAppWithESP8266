#include "Scheduler.h"
#include "MiniTimerOne.h"
#include "Arduino.h"

volatile bool timerFlag;

void timerHandler(void) {
    timerFlag = true;
}

void Scheduler::init(int basePeriod) {
    this->basePeriod = basePeriod;
    this->removeTasks();
    timerFlag = false;
    long period = 1000l * basePeriod;
    SchedulerTimer.init();
    SchedulerTimer.setPeriod(period);
    SchedulerTimer.attachInterrupt(timerHandler);
    SchedulerTimer.start();
}

void Scheduler::reset(int basePeriod) {
    SchedulerTimer.stop();
    SchedulerTimer.reset();
    this->init(basePeriod);
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS - 1) {
        taskList[this->nTasks] = task;
        this->nTasks++;
        return true;
    }
    else {
        return false;
    }
}

void Scheduler::schedule() {
    while (!timerFlag) {}
    timerFlag = false;

    for (int i = 0; i < this->nTasks; i++) {
        if (taskList[i]->isActive() && taskList[i]->updateAndCheckTime(basePeriod)) {
            taskList[i]->tick();
        }
    }
}

void Scheduler::removeTasks() {
    this->nTasks = 0;
}
