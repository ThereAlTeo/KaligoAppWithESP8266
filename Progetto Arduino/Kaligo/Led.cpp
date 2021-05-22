#include "Led.h"
#include "Arduino.h"

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
    digitalWrite(this->pin, LOW);
}

void Led::switchOff() {
    digitalWrite(this->pin, HIGH);
};
