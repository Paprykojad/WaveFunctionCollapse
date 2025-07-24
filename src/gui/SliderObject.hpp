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
        void (UiObject::*func)(f32);
        UiObject* target;

        bool revert;


        public:
        SliderObject(
          ObjectData object,
          std::string LeftText,
          std::string RightText,
          f32 min,
          f32 max,
          void (UiObject::*func)(f32),
          UiObject* target,
          bool revert
        );

        SliderObject (
          std::string LeftText,
          std::string RightText,
          f32 min,
          f32 max,
          void (UiObject::*func)(f32),
          UiObject* target,
          bool revert
        );

        void draw() override;
};
