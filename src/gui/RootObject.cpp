#include "RootObject.hpp"
#include "gui/UiObject.hpp"


RootObject::RootObject(u32 screenW, u32 screenH, u32 marginX, u32 marginY) :
    UiObject((ObjectData){
        // .posX = marginX + marginX,
        // .posY = marginY + marginY,
        .posX = 0,
        .posY = 0,
        .width = screenW,
        .height = screenH,
        .marginX = marginX,
        .marginY = marginY
        }, Horizontal) {}

void RootObject::draw() {}
