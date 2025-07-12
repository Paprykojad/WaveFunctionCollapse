#pragma once

#include <aliases.hpp>
#include <cstdint>
#include <raylib.h>
#include <functional>

inline bool operator==(const Color& a, const Color& b) {
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}


namespace std {
    template <>
    struct hash<Color> {
        std::size_t operator()(const Color& c) const noexcept {
            // Pack RGBA into a single 32-bit value and hash it
            std::uint32_t packed = (static_cast<std::uint32_t>(c.r) << 24) |
                (static_cast<std::uint32_t>(c.g) << 16) |
                (static_cast<std::uint32_t>(c.b) << 8) |
                static_cast<std::uint32_t>(c.a);
            return std::hash<std::uint32_t>{}(packed);
        }
    };
}

class ColorTable {
public:
    Color** data;

    ~ColorTable();

    u32 width, height;

    ColorTable(u32 width, u32 height); // constructor 1
    ColorTable(u32 width, u32 height, Color** data); // constructor 2
    ColorTable(ColorTable* src); // constructor 3

    void CopyTable(ColorTable* dest);
    void GetData(Color** src);
    Color Get(u32 y, u32 x);
    void Set(u32 y, u32 x, Color val);

    bool operator==(const ColorTable& other) const {
        if (this->height != other.height || this->height != other.height ) {
            return false;
        }

        for range(y, this->height) {
            for range(x, this->width) {
                if (other.data[y][x] != this->data[y][x]) {
                    return false;
                }
            }
        }
        return true;
    }
};
