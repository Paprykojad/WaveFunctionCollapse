#include <stdexcept>

#include "gui/ColorPickerObject.hpp"

#include <bits/error_constants.h>

#include "external/raylib.h"
#include "gui/UiObject.hpp"

void ColorPickerObject::draw() {
    i32 min = 0;
    if (this->width <= min || this->height <= min) {
        return;
    }

    GuiColorPicker(
            (Rectangle){
                .x = (f32)posX,
                .y = (f32)posY,
                .width = (f32)width - marginX,
                .height = (f32)height
            },
            this->text.c_str()
            , this->color);
}

ColorPickerObject::ColorPickerObject(ObjectData object, str text, Color *color) : UiObject(object, NoChildren) {
    this->text = text;
    if (color == nullptr) {
        throw std::invalid_argument("nullptr");
    }
    this->color = color;
    *(this->color) = WHITE;
}

ColorPickerObject::ColorPickerObject(str text, Color *color) : ColorPickerObject((ObjectData){}, text, color) {}
