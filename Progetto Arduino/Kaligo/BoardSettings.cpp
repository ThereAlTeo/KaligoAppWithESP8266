#include "BoardSettings.h"

bool interruptPinBoardAvailable(int pin) {
    bool contais = false;
    for (int i = 0; i < NUM_PINS_AVAILABLE; i++) {
        if (INTERRUPT_PIN_AVAILABLE[i] == pin) {
            return true;
        }
    }
    return contais;
}

int convertPinToArrayIndex(int pin) {
    switch (pin) {
    case 2: return 0;
    case 3: return 1;
    case 18: return 2;
    case 19: return 3;
    case 20: return 4;
    case 21: return 5;
    default: return -1;
    }
}