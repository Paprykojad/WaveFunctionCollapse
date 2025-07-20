//
// Created by fg on 7/17/25.
//
#pragma once

#include "Container.hpp"
#include <vector>
#include <tuple>

enum Mode {
    Vertical,
    Horizontal,
    NoChildren
};

class UiObject {
    protected:
        u32 posX, posY;
        u32 width, height;

        Container* myContainer;

        const u32 maxAmountOfChildren = 2;

        std::array<u32, 2> getMarginLengthSum();
        std::array<u32, 2> getChildWidth();

        Mode mode;
        f32 proportions;

    private:
        std::vector< std::tuple<Container, UiObject*> > childContainers;

        UiObject(std::array<u32, 4> arr);
        UiObject(std::array<u32, 4> arr, Mode mode, f32 proportions = 0.5f);

    public:
        virtual ~UiObject();

        UiObject(Container* container);
        UiObject(Container* container, Mode mode, f32 proportions);

        void AddChild(UiObject* object);

        virtual void draw() = 0;
};
