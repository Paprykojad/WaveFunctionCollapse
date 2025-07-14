#pragma once
#include <unordered_map>

#include "aliases.hpp"
#include "Color.hpp"

enum Direction {
    Top = 0,
    Right = 1,
    Bottom = 2,
    Left = 3
};

struct ColorCounter {
    std::unordered_map<Color, u32> direction[4];
    // 0 - top
    // 1 - right
    // 2 - bottom
    // 3 - left

    void addColor(Color col, u32 dir);
};

