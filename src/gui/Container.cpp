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

std::array<u32, 4> Container::GetCanvasData() {
    std::array<u32, 4> val = {
        posX + marginX/2,           // startX
        posY + marginY/2,           // startY
        posX + width - marginX/2,   // lengthX
        posY + height - marginY/2   // lengthY
    };
    return val;
}

