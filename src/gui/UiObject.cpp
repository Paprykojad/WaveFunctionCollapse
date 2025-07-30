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
		width = (this->width - (amountOfChildren+1)*this->inheritableMarginX)/amountOfChildren;
		height = this->height - 2*this->inheritableMarginY;

        posX = this->posX + childNumber * (width + this->inheritableMarginX) + this->inheritableMarginX;
        posY = this->posY + this->inheritableMarginY;

        marginX = this->marginX;
        marginY = this->marginY;
	} else {
		width = this->width - 2*this->marginX;
		height = (this->height - (amountOfChildren+1)*this->marginY)/amountOfChildren;

        posY = this->posY + childNumber * (height + this->marginY) + this->marginY;
        posX = this->posX + this->marginX;

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

void UiObject::drawAll() {
	this->draw();
	for range(i, children.size()) {
		children[i]->drawAll();
	}
}

void UiObject::resize(u32 idx) {
	if (this->mode == NoChildren) {
		throw std::logic_error("shouldn't have children");
	}


	if (this->mode == Horizontal) {

		u32 noMargin = (this->width - (1+children.size())*this->marginX);
		if (children.size() == 2) {
			children[idx]->width = noMargin - (idx == 0 ? splitRatio : 1.0f - splitRatio)*noMargin;
		} else {
			children[idx]->width = noMargin;
		}
		children[idx]->height = this->height - 2*this->marginY;

		u32 sum = 0;
		for range(i, idx) {
			sum += children[i]->width;
			sum += children[i]->marginX;
		}
		sum += marginX;

		children[idx]->posX = this->posX + sum;
		children[idx]->posY = this->posY + marginY;

	} else {

		u32 noMargin = (this->height - (1+children.size())*this->marginY);
		if (children.size() == 2) {
			children[idx]->height = noMargin - (idx == 0 ? splitRatio : 1.0f - splitRatio)*noMargin;
		} else {
			children[idx]->width = noMargin;
		}
		children[idx]->width = this->width - 2*this->marginX;

		u32 sum = 0;
		for range(i, idx) {
			sum += children[i]->height;
			sum += children[i]->marginY;
		}
		sum += marginY;
		children[idx]->posY = this->posY + sum;
		children[idx]->posX = this->posX + marginX;
	}
}

void UiObject::resizeAll(f32 ratio) {
	this->splitRatio = ratio;

	for range(i, children.size()) {
	resize(i);
}

for range(i, children.size()) {
children[i]->resizeAll(children[i]->splitRatio);
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
