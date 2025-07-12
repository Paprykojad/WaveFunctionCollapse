#include <exception>
#include <raylib.h>
#include <aliases.hpp>
#include "ColorTable.hpp"


#include <stdexcept>


ColorTable::ColorTable(u32 width, u32 height) {
    this->width = width;
    this->height = height;
    data = new Color*[height];
    for (u32 i = 0; i < height; i++) {
        data[i] = new Color[width];
    }
}

ColorTable::ColorTable(u32 width, u32 height, Color** data) {
    this->width = width;
    this->height = height;
    this->data = new Color*[height];
    for range(y, height) {
        this->data[y] = new Color[width];
    }

    for range(y, height) {
        for range(x, width) {
            this->data[y][x] = data[y][x];
        }
    }
}

ColorTable::ColorTable(ColorTable* src) {
    if (src == nullptr) {
        throw std::invalid_argument("nullptr");
    }

    this->width = src->width;
    this->height = src->height;

    this->data = new Color*[height];
    for range(y, this->height) {
        this->data[y] = new Color[width];
    }

    src->CopyTable(this);
}


ColorTable::~ColorTable() {
    for (u32 i = 0; i < height; i++) {
        if (data[i] != nullptr) {
            free(data[i]);
        }
    }
    if (data != nullptr) {
        free(data);
    }
}

void ColorTable::CopyTable(ColorTable* dest) {
    if (dest == nullptr) {
        throw std::invalid_argument("nullptr");
    }

    if (this->width != dest->width || this->height != dest->height) {
        throw std::invalid_argument("wrong dimensions");
    }

    for (u32 i = 0; i < height; i++) {
        if (dest->data[i] != nullptr) {
            free(dest->data[i]);
        }
    }
    if (dest->data != nullptr) {
        free(dest->data);
    }
    dest->data = new Color*[height];
    for range(i, height) {
        dest->data[i] = new Color[width];
    }

    for (u32 y = 0; y < this->height; y++) {
        for (u32 x = 0; x < this->width; x++) {
            dest->data[y][x] = this->data[y][x];
        }
    }
}

void ColorTable::GetData(Color** src) {
    for range(y, this->height) {
        for range(x, this->width) {
            this->data[y][x] = src[y][x];
        }
    }
}


Color ColorTable::Get(u32 y, u32 x) {
    if (y >= this->height || x >= this->width) {
        throw std::invalid_argument("index out of range");
    }

    return this->data[y][x];
}

void ColorTable::Set(u32 y, u32 x, Color val) {
    if (y >= this->height || x >= this->width) {
        throw std::invalid_argument("index out of range");
    }

    this->data[y][x] = val;
}
