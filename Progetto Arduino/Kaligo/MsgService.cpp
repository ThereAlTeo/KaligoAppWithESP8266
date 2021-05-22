#include "Arduino.h"
#include "MsgService.h"

MsgService::MsgService(int rxPin, int txPin) {
    this->channel = new SoftwareSerial(rxPin, txPin);
}

void MsgService::init() {
    this->content.reserve(256);
    this->channel->begin(38400);
}

void MsgService::sendMsg(const String& msg) {
    this->channel->println(msg);
}

void MsgService::sendCommand(const String& key, const String& values) {
    this->sendMsg(key + ":" + values);
}

bool MsgService::sendMsg(Msg msg) {
    this->sendMsg(msg.getContent());
}

bool MsgService::isMsgAvailable() {
    return this->channel->available();
}

Msg* MsgService::receiveMsg() {
    while (this->channel->available()) {
        char ch = (char)this->channel->read();
        if (ch == '\n') {
            Msg* msg = new Msg(this->content);
            this->content = "";
            return msg;
        }
        else {
            this->content += ch;
        }
    }

    return NULL;
}
