#pragma once

#include <aliases.hpp>
#include "gui/UiObject.hpp"
#include "algorithm/Color.hpp"
#include <external/raylib.h>
#include <external/raygui.h>

class ColorPickerObject : public UiObject {
    private:
        str text;

    public:
        Color *color;

        ColorPickerObject(ObjectData object, str text, Color *color);
        ColorPickerObject(str text, Color *color);
        void draw() override;
};
