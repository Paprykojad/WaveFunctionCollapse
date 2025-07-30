#pragma once

#include <aliases.hpp>
#include "gui/UiObject.hpp"
#include "algorithm/Color.hpp"
#include <external/raylib.h>
#include <external/raygui.h>

class ColorPickerObject : public UiObject {
    private:
        Color color;
        str text;

    public:
        ColorPickerObject(ObjectData object, str text);
        ColorPickerObject(str text);
        void draw() override;
};
