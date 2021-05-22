#include "BluetoothTask.h"
#include "CommonSettings.h"

BluetoothTask::BluetoothTask(MsgService* msgService) {
    this->msgService = msgService;
}

void BluetoothTask::tick() {
    if (this->msgService->isMsgAvailable()) {
        Msg* msg = this->msgService->receiveMsg();
        String content = msg->getContent();
        Serial.print(content);
        if (content.indexOf("-") >= 0) {
            content = content.substring(content.indexOf("-") + 1);
            int endOfType = content.indexOf(":");
            this->handleMessage(content.substring(0, endOfType), content.substring(endOfType + 1, content.length()));
        }

        delete msg;
    }
}

void BluetoothTask::init(int period) {
    Task::init(period);
}

void BluetoothTask::handleMessage(String command, String value) {
    if (command.equals(SATURATION_SECOND_COMMAND)) {
        this->setCycleTimeNotify(NEBULIZATION, value.toInt());
    }
    else if (command.equals(FOTOCATALISI_SECOND_COMMAND)) {
        this->setCycleTimeNotify(PHOTOCATALYSIS, value.toInt());
    }
    else if (command.equals(NIGHT_SECOND_COMMAND)) {
        this->setCycleTimeNotify(NIGHT_MODE, value.toInt());
    }
    else if (command.equals(START_COMMAND)) {
        this->startNotify();
    }   
    else if (command.equals(STOP_COMMAND)) {
        this->stopNotify();
    }
    else if (command.equals(OPEN_DOOR_FRONT_COMMAND)) {  
        this->openFrontDoorNotify();
    }
    else if (command.equals(OPEN_DOOR_BACK_COMMAND)) {    
        this->openBackDoorNotify();
    }
}

void BluetoothTask::startNotify() {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->start();
    }
}

void BluetoothTask::stopNotify() {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->stop();
    }
}

void BluetoothTask::setCycleTimeNotify(CycleMode cycle, int newTime) {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->setCycleTime(cycle, newTime);
    }
}

void BluetoothTask::setCycleModeNotify(CycleMode newCycleMode) {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->setCycleMode(newCycleMode);
    }
}

void BluetoothTask::openFrontDoorNotify() {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->openFrontDoor();
    }
}

void BluetoothTask::openBackDoorNotify() {
    for (int i = 0; i < this->nListeners; i++) {
        this->listeners[i]->openBackDoor();
    }
}
