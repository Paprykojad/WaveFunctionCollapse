//
// Created by fg on 7/17/25.
//

#pragma once
#include "aliases.hpp"
#include <array>

class Container {
    private:

    u32 posX, posY;
    u32 width, height;
    u32 marginX, marginY;

    std::array<u32, 4> GetCanvasData();


    public:
    
    Container( u32 posX, u32 posY, u32 width, u32 height, u32 marginX, u32 marginY );
};
