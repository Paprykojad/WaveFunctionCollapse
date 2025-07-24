#pragma once

#include "UiObject.hpp"

class RootObject : public UiObject {
    public:
        RootObject(u32 screenW, u32 screenH, u32 marginX, u32 marginY);
};
