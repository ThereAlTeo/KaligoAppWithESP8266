#ifndef __BOARDSETTINGS__
#define __BOARDSETTINGS__

const int INTERRUPT_PIN_AVAILABLE[] = { 2, 3, 18, 19, 20, 21 };
const int NUM_PINS_AVAILABLE = (sizeof(INTERRUPT_PIN_AVAILABLE) / sizeof(INTERRUPT_PIN_AVAILABLE[0]));

bool interruptPinBoardAvailable(int pin);

int convertPinToArrayIndex(int pin);

#endif 

