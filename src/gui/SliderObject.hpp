#pragma once

#include "UiObject.hpp"
#include <external/raylib.h>
#include <string>

class SliderObject : public UiObject {
    private:
        std::string LeftText;
        std::string RightText;
        f32 val;
        f32 min, max;
        void (*func)(f32);


    public:
        SliderObject(ObjectData object, std::string LeftText, std::string RightText, f32 min, f32 max,  void (*func)(f32), Mode mode = NoChildren);
        SliderObject (std::string LeftText, std::string RightText, f32 min, f32 max,  void (*func)(f32), Mode mode = NoChildren);
        void draw() override;
};
