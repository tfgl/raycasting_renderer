#include "level.h"
#include <cstdlib>
#include <memory.h>

Level::Level(size_t width, std::size_t height)
: _width(width), _height(height) {
    _map = (char*)malloc(sizeof(char) * width * height);
}

char Level::get(size_t x, size_t y) {
    return _map[y*_width + x];
}

void Level::set(size_t x, size_t y, char c) {
    _map[y*_width+x] = c;
}

void Level::set(char* map) {
    memcpy(_map, map, _width * _height);
    flip();
}

void Level::flip() {
    char* tmp = (char*)malloc(sizeof(char) * _width);

    for (int y=0; y<_height/2; y++) {
        memcpy(tmp, _map + _width * y, _width);

        memcpy(_map + _width * y,
               _map + _width * (_height - y -1),
               _width);

        memcpy(_map + _width * (_height - y -1),
               tmp,
               _width);
    }
}
