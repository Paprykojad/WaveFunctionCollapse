#include "GroupBoxObject.hpp"
#include "gui/UiObject.hpp"
#include "external/raylib.h"
#include "external/raygui.h"


GroupBoxObject::GroupBoxObject(Container* container, std::string text) : UiObject(container) {
    this->text = text;
}

GroupBoxObject::GroupBoxObject(Container* container, std::string text, Mode mode, f32 proportions) : UiObject(container, mode, proportions) {
    this->text = text;
}

void GroupBoxObject::draw() {
    Rectangle rect = (Rectangle){
        .x = (f32)this->posX,
        .y = (f32)this->posY,
        .width = (f32)this->width,
        .height = (f32)this->height,
    };
    GuiGroupBox(rect, this->text.c_str());
}
