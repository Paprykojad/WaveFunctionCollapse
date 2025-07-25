#include "BlankObject.hpp"

BlankObject::BlankObject(ObjectData data, Mode mode) : UiObject(data, mode) {
	this->marginX = 0;
	this->marginY = 0;
	this->posX -= inheritableMarginX;
	this->posY -= inheritableMarginY;
}

BlankObject::BlankObject(Mode mode) : UiObject((ObjectData){}, mode) {
}

void BlankObject::draw() {}
