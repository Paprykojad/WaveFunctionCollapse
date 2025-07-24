#include "RootObject.hpp"
#include "gui/UiObject.hpp"


RootObject::RootObject(u32 screenW, u32 screenH, u32 marginX, u32 marginY) : 
    UiObject((ObjectData){
        .posX = marginX,
        .posY = marginY,
        .width = screenW - 2*marginX,
        .height = screenH - 2*marginY,
        .marginX = marginX,
        .marginY = marginY
        }, Horizontal) {}
