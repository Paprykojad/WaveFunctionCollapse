#pragma once

#include "UiObject.hpp"

class RootObject : public UiObject {
    private:
        i32 lastW, lastH;

    public:
        RootObject(u32 screenW, u32 screenH, u32 marginX, u32 marginY);
        void draw() override;
        void updateSize();
};
