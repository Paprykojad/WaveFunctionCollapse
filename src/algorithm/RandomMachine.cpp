#include <chrono>
#include <random>
#include <stdexcept>


#include "RandomMachine.hpp"
#include "Learner.hpp"
#include "external/raylib.h"


RandomMachine::RandomMachine(ColorTable* data) : Learner(data), generator(std::chrono::high_resolution_clock::now().time_since_epoch().count()), dist(1, this->data.width*this->data.height) {
}

Color RandomMachine::GetRandomColor(u32 y, u32 x, u32 direction) {
    ColorCounter* colorCounter = &(this->colorCounts[this->data.Get(y, x)]);
    u32 amountOfColors = colorCounter->direction[direction].size();

    u32 randomNumber = dist(generator) % amountOfColors;

    for (auto col : colorCounter->direction[direction]) {
        if (col.second >= randomNumber) {
            return col.first;
        } else {
            randomNumber -= col.second;
        }
    }
    throw std::logic_error("nie wylosowalo klasy");
}
