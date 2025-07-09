#include <exception>

#include "ColorTable.h"

#include <stdexcept>

ColorTable::ColorTable(u32 width, u32 height) {
    this->width = width;
    this->height = height;
    data = new Color*[height];
    for (u32 i = 0; i < height; i++) {
        data[i] = new Color[width];
    }
}


ColorTable::~ColorTable() {
    for (u32 i = 0; i < height; i++) {
        free(data[i]);
    }
    free(data);
}

void ColorTable::Copy(ColorTable *dest) {
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

    for (u32 y = 0; y < this->height; y++) {
        for (u32 x = 0; x < this->width; x++) {
            dest->data[y][x] = this->data[y][x];
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
