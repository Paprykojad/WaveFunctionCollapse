#pragma once

#include "UiObject.hpp"
#include <raylib.h>
#include <string>

class GroupBoxObject : UiObject {
    private:
        std::string text;

    public:
        GroupBoxObject(Container* container, std::string text);
        GroupBoxObject(Container* container, std::string text, Mode mode, f32 proportions = 0.5f);

        void draw() override;
};

