//
// Created by fg on 7/17/25.
//

#include "Container.hpp"

Container::Container( u32 posX, u32 posY, u32 width, u32 height, u32 marginX, u32 marginY ) {
    this->posX = posX;
    this->posY = posY;
    this->width = width;
    this->height = height;
    this->marginX = marginX;
    this->marginY = marginY;
}

Container::Container(std::array<u32, 6> arr) {
    this->posX = arr[0];
    this->posY = arr[1];
    this->width = arr[2];
    this->height = arr[3];
    this->marginX = arr[4];
    this->marginY = arr[5];
}

std::array<u32, 4> Container::CanvasDimensions() {
    std::array<u32, 4> val = {
        posX + marginX/2,           // startX
        posY + marginY/2,           // startY
        // posX + width - marginX/2,   // lengthX
        // posY + height - marginY/2   // lengthY
        width - marginX,
        height - marginY
    };
    return val;
}

std::array<u32, 6> Container::GetAllCanvasData() {
    std::array<u32, 6> val = {
        this->posX,
        this->posY,
        this->width,
        this->height,
        this->marginX,
        this->marginY
    };
    return val;
}

