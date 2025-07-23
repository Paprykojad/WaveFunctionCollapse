//
// Created by fg on 7/17/25.
//

#pragma once
#include "aliases.hpp"
#include <array>

class Container {

    public:

        u32 posX, posY;
        u32 width, height;
        u32 marginX, marginY;

        Container( u32 posX, u32 posY, u32 width, u32 height, u32 marginX, u32 marginY );
        Container(std::array<u32, 6> arr);

        std::array<u32, 6> GetAllCanvasData();
        std::array<u32, 4> CanvasDimensions();

};
