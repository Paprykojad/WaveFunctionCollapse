#include "GroupBoxObject.hpp"
#include "gui/UiObject.hpp"
#include <aliases.hpp>

#include <external/raylib.h>
#include <external/raygui.h>

GroupBoxObject::GroupBoxObject(ObjectData data, Mode mode, std::string text) : UiObject(data, mode) {
    this->text = text;
}

GroupBoxObject::GroupBoxObject(Mode mode, std::string text) : UiObject((ObjectData){}, mode) {
    this->text = text;
}

void GroupBoxObject::draw() {
    if (this->width > 0 && this->height > 0) {
        Rectangle rect = (Rectangle){
            .x = (f32) this->posX,
            .y = (f32) this->posY,
            .width = (f32) this->width,
            .height = (f32) this->height,
        };
        GuiGroupBox(rect, this->text.c_str());
    }
}
