#include "gui/ColorPickerObject.hpp"
#include "external/raylib.h"
#include "gui/UiObject.hpp"

void ColorPickerObject::draw() {
    GuiColorPicker(
            (Rectangle){
                .x = (f32)posX,
                .y = (f32)posY,
                .width = (f32)width - marginX,
                .height = (f32)height
            },
            this->text.c_str()
            , &(this->color));
}

ColorPickerObject::ColorPickerObject(ObjectData object, str text) : UiObject(object, NoChildren) {
    this->text = text;
    this->color = WHITE;
}

ColorPickerObject::ColorPickerObject(str text) : ColorPickerObject((ObjectData){}, text) {}
