#pragma once
#include <unordered_map>
#include <aliases.hpp>

#include "ColorTable.hpp"
#include "Color.hpp"
#include "ColorCounter.hpp"

class Learner {
public:
    ColorTable data;

    std::unordered_map<Color, ColorCounter> colorCounts;
    std::unordered_map<Color, u32> coloredPixelsCount;

    Learner(ColorTable* data);

    Color selectColor(i32 y, i32 x);
    void registerPixel(u32 y, u32 x);

    
};
