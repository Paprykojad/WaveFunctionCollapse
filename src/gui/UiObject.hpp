//
// Created by fg on 7/17/25.
//
#pragma once

#include <vector>
#include "Container.hpp"

class UiObject {
    private:

    Container& parentContainer;
    std::vector<Container> childContainers;


    public:

    UiObject(Container& parentContainer);

    virtual void draw();
};
