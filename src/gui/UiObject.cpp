#include <aliases.hpp>
#include <stdexcept>
#include "UiObject.hpp"

void UiObject::setValues(ObjectData data) {
	this->posX = data.posX;
	this->posY = data.posY;
	this->width = data.width;
	this->height = data.height;
	this->marginX = data.marginX;
	this->marginY = data.marginY;
}

UiObject::UiObject(ObjectData data, Mode mode = NoChildren) {
    setValues(data);
	this->mode = mode;

}

ObjectData UiObject::createObjectData(u32 amountOfChildren, u32 childNumber) {
	if (this->mode == NoChildren) {
		throw std::logic_error("NoChildren mode");
	}

	u32 posX;
	u32 posY;
	u32 width;
	u32 height;
	u32 marginX;
	u32 marginY;

	if (this->mode == Horizontal) {
		width = this->width - (amountOfChildren-1)*this->marginX;
		height = this->height;

        posX = this->posX + childNumber * (width + this->marginX);
        posY = this->posY;

        marginX = this->marginX;
        marginY = this->marginY;

	} else {
		width = this->width;
		height = this->height - (amountOfChildren-1)*this->marginY;

        posY = this->posY + childNumber * (width + this->marginY);
        posX = this->posX;

        marginX = this->marginX;
        marginY = this->marginY;

	}

	return (ObjectData){
        .posX = posX,
        .posY = posY,
        .width = width,
        .height = height,
        .marginX = marginX,
        .marginY = marginY,
    };
}

void UiObject::addChild(UiObject* object) {
    if (this->childrenMax == children.size()) {
        throw std::logic_error("too many children");
    }

    this->children.push_back(object);
    for range(i, children.size()) {
        children[i]->setValues(createObjectData(children.size(), i));
    }
}

void UiObject::draw() {
	throw std::logic_error("empty UiObject is drawing");
}

UiObject::~UiObject() {
	for range(i, children.size()) {
		delete children[i];
	}
}
