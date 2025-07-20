//
// Created by fg on 7/17/25.
//

#include "UiObject.hpp"
#include "gui/Container.hpp"
#include "raylib.h"
#include <array>
#include <stdexcept>

UiObject::UiObject(std::array<u32, 4> arr, Mode mode, f32 proportions) {
    this->posX = arr[0];
    this->posY = arr[1];
    this->width = arr[2];
    this->height = arr[3];
    
    this->mode = mode;
    this->proportions = proportions;
}

UiObject::UiObject(std::array<u32, 4> arr) {
    this->posX = arr[0];
    this->posY = arr[1];
    this->width = arr[2];
    this->height = arr[3];
    
    this->mode = NoChildren;
}


UiObject::UiObject(Container* container, Mode mode, f32 proportions) : UiObject(container->CanvasDimensions(), mode, proportions) {
    this->myContainer = container;
}

UiObject::UiObject(Container* container) : UiObject(container->CanvasDimensions()) {
    this->myContainer = container;
}

std::array<u32, 2> UiObject::getMarginLengthSum() {

    if(this->childContainers.size() == 0) {
        throw std::logic_error("no children");
    }

    std::array<u32, 2> arr;

    arr[0] = (this->childContainers.size() + 1)*myContainer->GetAllCanvasData()[4];
    arr[1] = (this->childContainers.size() + 1)*myContainer->GetAllCanvasData()[5];

    return arr;
}

std::array<u32, 2> UiObject::getChildWidth() {

    if(this->childContainers.size() == 0) {
        throw std::logic_error("no children");
    }

    std::array<u32, 2> arr;

    arr[0] = this->width-this->getMarginLengthSum()[0];
    arr[1] = this->width-this->getMarginLengthSum()[1];

    return arr;
}

void UiObject::AddChild(UiObject* object) {
    if (childContainers.size() >= this->maxAmountOfChildren) {
        delete object;
        throw std::logic_error("to many children");
    }

    if (object == nullptr) {
        throw std::invalid_argument("nullptr");
    }

    Container c(
            this->myContainer->CanvasDimensions()[4]*(1+this->childContainers.size())+getChildWidth()[0],
            this->myContainer->CanvasDimensions()[5]*(1+this->childContainers.size())+getChildWidth()[1],
            getChildWidth()[0],
            getChildWidth()[1],
            this->myContainer->CanvasDimensions()[4],
            this->myContainer->CanvasDimensions()[5]
            );



    // std::tuple<Container, UiObject*> t;
}

UiObject::~UiObject() {
    for (auto t : this->childContainers) {
        if (get<1>(t) != nullptr) {
            delete get<1>(t);
        }
    }
}


