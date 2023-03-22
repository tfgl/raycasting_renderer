#pragma once

#include "type.h"

class Level {
    char* _map;

    void flip();

public:
    size_t _width, _height;

    Level(size_t width, size_t height);

    char get(size_t x, size_t y);
    void set(size_t x, size_t y, char c);
    void set(char* map);
};
