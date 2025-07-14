#pragma once

#include "ColorTable.hpp"
#include "Learner.hpp"

class RandomMachine : public Learner {
    public:
        RandomMachine(ColorTable* data);
};
