#include "Learner.hpp"
#include "ColorCounter.hpp"
#include "ColorTable.hpp"

#include <stdexcept>

Color Learner::selectColor(i32 y, i32 x) {
    if (y < 0 || x < 0) {
        throw std::invalid_argument("intex out of range");
    }

    u32 ux, uy;
    ux = (u32)x;
    uy = (u32)y;

    if (uy >= this->data.height || ux >= this->data.width ) {
        throw std::invalid_argument("intex out of range");
    }

    return this->data.Get(uy, ux);
}

void Learner::registerPixel(u32 y, u32 x) {
    Color myColor = selectColor(y, x);

    i32 dimentions[4][2] = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
    };

    for range(i, 4) {
        Color currentColor;
        try {
            currentColor = selectColor(y+dimentions[i][0], x+dimentions[i][1]);
        } catch (std::exception& e) {
            continue;
        }

        colorCounts[myColor].addColor(currentColor, i);
    }
}


Learner::Learner(ColorTable* data) : data(data) {
    for range(y, data->height) {
        for range (x, data->width) {
            registerPixel(y, x);
            if (!coloredPixelsCount.contains(data->Get(y, x))) {
                coloredPixelsCount[data->Get(y, x)] = 1;
            } else {
                coloredPixelsCount[data->Get(y, x)]++;
            }
        }
    }
}
