#pragma once

#include "type.h"
#include <cstddef>

class Level {
    char* _map = NULL;

    void flip();

public:
    size_t _width, _height;

    Level(size_t width, size_t height, char* map);

    char get(size_t x, size_t y);
    void set(size_t x, size_t y, char c);
    void set(size_t width, size_t height, char* map);
};
