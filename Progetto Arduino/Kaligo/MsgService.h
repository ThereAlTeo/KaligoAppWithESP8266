#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"
#include <SoftwareSerial.h>

class Msg {
    String content;

public:
    Msg(const String& content) {
        this->content = content;
    }

    String getContent() {
        return content;
    }
};

class MsgService {
private:
    String content;
    SoftwareSerial* channel;

public:
    MsgService(int rxPin, int txPin);
    void init();
    bool isMsgAvailable();
    Msg* receiveMsg();
    void sendMsg(const String& msg);
    void sendCommand(const String& key, const String& values);
    bool sendMsg(Msg msg);
};

#endif
