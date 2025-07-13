#pragma once

#include <aliases.hpp>
#include <cstdint>
#include "Color.hpp"


class ColorTable {
public:
    Color** data;

    ~ColorTable();

    u32 width, height;

    ColorTable(u32 width, u32 height); // constructor 1
    ColorTable(u32 width, u32 height, Color** data); // constructor 2
    ColorTable(ColorTable* src); // constructor 3

    void CopyTable(ColorTable* dest);
    void GetData(Color** src);
    Color Get(u32 y, u32 x);
    void Set(u32 y, u32 x, Color val);

    bool operator==(const ColorTable& other) const ;
};
