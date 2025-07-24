#pragma once

#include "UiObject.hpp"
#include <external/raylib.h>
#include <string>

class GroupBoxObject : public UiObject {
    private:
        std::string text;

    public:
        GroupBoxObject(ObjectData data, Mode mode, std::string text);
        GroupBoxObject(Mode mode, std::string text);
        void draw() override;
};
