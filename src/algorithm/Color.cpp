#include "Color.hpp"
#include <cstdint>      // for uint32_t
#include <functional>   // for std::hash<uint32_t>

// operator== definition
bool operator==(const Color& lhs, const Color& rhs) noexcept {
    return lhs.r == rhs.r
        && lhs.g == rhs.g
        && lhs.b == rhs.b
        && lhs.a == rhs.a;
}

// std::hash<Color>::operator() definition
std::size_t std::hash<Color>::operator()(const Color& color) const noexcept {
    // pack components into a 32-bit integer, then hash
    uint32_t packed =
          (uint32_t(color.r) << 24)
        | (uint32_t(color.g) << 16)
        | (uint32_t(color.b) <<  8)
        |  uint32_t(color.a);
    return std::hash<uint32_t>{}(packed);
}