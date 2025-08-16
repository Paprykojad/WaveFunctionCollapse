#include "PixelDisplayerObject.hpp"
#include "external/raylib.h"
#include "gui/UiObject.hpp"

#include <iostream>

PixelDisplayerObject::PixelDisplayerObject(ObjectData object, ColorTable *colorTable, bool drawable) : UiObject(
    object, NoChildren) {
    this->colorTable = colorTable;
    this->drawable = drawable;
}

PixelDisplayerObject::PixelDisplayerObject(ColorTable *colorTable, bool drawable) : PixelDisplayerObject(
    (ObjectData){}, colorTable, drawable) {
}

void PixelDisplayerObject::draw() {
    if (drawable) {
        Vector2 mPos = GetMousePosition();

        if (
            (mPos.x > this->posX && mPos.x < (f32) (this->posX + this->width)) &&
            (mPos.y > this->posY && mPos.y < (f32) (this->posY + this->height))
        ) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            // if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
                u32 pxY = (mPos.y - this->posY) / (this->height / this->colorTable->height);
                u32 pxX = (mPos.x - this->posX) / (this->width / this->colorTable->width);

                if (pxY < this->colorTable->height && pxX < this->colorTable->width) {
                    this->colorTable->Set(pxY, pxX, this->drawColor);
                }
            }
        }
    }

    u32 pxW = this->width / this->colorTable->width;
    u32 pxH = this->height / this->colorTable->height;

    for range(y, this->colorTable->width) {
        for range(x, this->colorTable->height) {
            Rectangle rec = (Rectangle){
                .x = (f32) (this->posX + x * pxW),
                .y = (f32) (this->posY + y * pxH),
                .width = (f32) pxW,
                .height = (f32) pxH,
            };
            DrawRectangleRec(rec, this->colorTable->Get(y, x));
        }
    }
}
