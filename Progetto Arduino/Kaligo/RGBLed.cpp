#include "Led.h"
#include "Arduino.h"
#include "RGBLed.h"

RGBLed::RGBLed(int redChannel, int blueChannel, int greenChannel) {
	this->redChannel = new Led(redChannel);
	this->blueChannel = new Led(blueChannel);
	this->greenChannel = new Led(greenChannel);
	this->color = BLUE;
}

void RGBLed::switchOn() {
	switch (this->color)
	{
	case RED:
		this->redChannel->switchOn();
		break;
	case GREEN:
		this->greenChannel->switchOn();
		break;
	case WHITE:
		this->redChannel->switchOn();
		this->blueChannel->switchOn();
		this->greenChannel->switchOn();
		break;
	case YELLOW:
		this->redChannel->switchOn();
		this->greenChannel->switchOn();
		break;
	case LIGHTBLUE:
		this->greenChannel->switchOn();
		this->blueChannel->switchOn();
		break;
	case PURPLE:
		this->redChannel->switchOn();
		this->blueChannel->switchOn();
		break;
	case BLUE:
	default:
		this->blueChannel->switchOn();
		break;
	}
}

void RGBLed::switchOff() {
	this->redChannel->switchOff();
	this->blueChannel->switchOff();
	this->greenChannel->switchOff();
}

void RGBLed::setColor(Color color) {
	if (this->color != color) {
		this->switchOff();
		this->color = color;
		this->switchOn();
	}	
}
