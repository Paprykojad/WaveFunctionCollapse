#pragma once

#include <cstdint>
#include <functional>

// typedef struct Color {
//     unsigned char r; // Color red value
//     unsigned char g; // Color green value
//     unsigned char b; // Color blue value
//     unsigned char a; // Color alpha value
// } Color;

#include <raylib.h>

bool operator==(const Color& lhs, const Color& rhs) noexcept;

// hash specialization declaration
namespace std {
    template <>
    struct hash<Color> {
        std::size_t operator()(const Color& color) const noexcept;
    };
}