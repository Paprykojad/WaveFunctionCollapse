#pragma once

#include "UiObject.hpp"

class BlankObject : public UiObject {
    public:
        BlankObject(ObjectData data, Mode mode = Horizontal);
        BlankObject(Mode mode);
        void draw() override;
};
