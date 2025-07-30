#include "RootObject.hpp"
#include <external/raylib.h>


RootObject::RootObject(u32 screenW, u32 screenH, u32 marginX, u32 marginY) :
    UiObject((ObjectData){
            // .posX = marginX + marginX,
            // .posY = marginY + marginY,
            .posX = 0,
            .posY = 0,
            .width = screenW,
            .height = screenH,
            .marginX = marginX,
            .marginY = marginY,
            }, Horizontal) {
        this->splitRatio = 0.0f;
        this->childrenMax = 1;
        this->lastW = GetScreenWidth();
        this->lastH = GetScreenHeight();
    }

void RootObject::draw() {}

void RootObject::updateSize() {
    if (GetScreenHeight() != this->lastH || GetScreenWidth() != this->lastW) {
        lastW = GetScreenWidth();
        lastH = GetScreenHeight();

        this->width = lastW;
        this->height = lastH;
        resizeAll(this->splitRatio);
    }
}
