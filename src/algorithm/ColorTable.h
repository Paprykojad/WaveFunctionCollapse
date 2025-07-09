#pragma once

#include <raylib.h>
#include <aliases.h>

class ColorTable {
private:
    Color **data;

    ~ColorTable();

public:
    u32 width, height;

    ColorTable(u32 width, u32 height);

    void Copy(ColorTable* dest);
    Color Get(u32 y, u32 x);
    void Set(u32 y, u32 x, Color val);
};
