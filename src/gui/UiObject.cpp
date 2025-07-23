//
// Created by fg on 7/17/25.
//

#include "UiObject.hpp"
#include "gui/Container.hpp"
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

// void UiObject::resize(Container* container) {
//
//     this->posX = arr[0];
//     this->posY = arr[1];
//     this->width = arr[2];
//     this->height = arr[3];
//     
//     this->mode = NoChildren;
// }


UiObject::UiObject(Container* container, Mode mode, f32 proportions) : UiObject(container->CanvasDimensions(), mode, proportions) {
    this->myContainer = container;
}

UiObject::UiObject(Container* container) : UiObject(container->CanvasDimensions()) {
    this->myContainer = container;
}

std::array<u32, 2> UiObject::getMarginDimentionsSum(u32 childerenAmount) {

    if (this->childContainers.size() == 0) {
        throw std::logic_error("no children");
    }

    std::array<u32, 2> arr;

    arr[0] = (childerenAmount - 1)*myContainer->GetAllCanvasData()[4];
    arr[1] = (childerenAmount - 1)*myContainer->GetAllCanvasData()[5];

    return arr;
}

std::array<u32, 2> UiObject::getChildDimentions(u32 childrenAmount) {

    if (this->childContainers.size() == 0) {
        throw std::logic_error("no children");
    }

    std::array<u32, 2> arr;

    arr[0] = this->width - this->getMarginDimentionsSum(childrenAmount)[0];
    arr[1] = this->height - this->getMarginDimentionsSum(childrenAmount)[1];

    return arr;
}

void UiObject::resizeAll() {
    u32 childrenAmount = this->childContainers.size();

    for range(i, childrenAmount) {
        std::array<u32, 2> childDimentions = getChildDimentions(childrenAmount + 1);
        std::array<u32, 6> canvasData =  std::get<0>(this->childContainers[i]).GetAllCanvasData();

        std::get<0>(this->childContainers[i]).width = childDimentions[0];
        std::get<0>(this->childContainers[i]).height = childDimentions[1];

        std::get<0>(this->childContainers[i]).posX = this->posX + (i-1)*(canvasData[4]);
        std::get<0>(this->childContainers[i]).posY = this->posY + (i-1)*(canvasData[5]);

        std::array<u32, 4> newCanvasDimensions = std::get<0>(this->childContainers[i]).CanvasDimensions();


        std::get<1>(this->childContainers[i])->posX = newCanvasDimensions[0];
        std::get<1>(this->childContainers[i])->posY = newCanvasDimensions[1];
        std::get<1>(this->childContainers[i])->width = newCanvasDimensions[2];
        std::get<1>(this->childContainers[i])->height = newCanvasDimensions[3];
    }
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
//          containers starting coordinates         
            this->myContainer->CanvasDimensions()[0]
            );
}

UiObject::~UiObject() {
    for (auto t : this->childContainers) {
        if (get<1>(t) != nullptr) {
            delete get<1>(t);
        }
    }
}


