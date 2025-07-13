#include "ColorCounter.hpp"

void ColorCounter::addColor(Color col, u32 dir) {
    if (!direction[dir].contains(col)) {
        direction[dir][col] = 1;
    }
    else {
        direction[dir][col]++;
    }
}
