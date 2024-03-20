#include "level.h"
#include <cstdlib>
#include <memory.h>

Level::Level(size_t width, size_t height, char* map) {
    set(width, height, map);
}

char Level::get(size_t x, size_t y) {
    return _map[y*_width + x];
}

void Level::set(size_t x, size_t y, char c) {
    _map[y*_width+x] = c;
}

void Level::set(size_t width, size_t height, char* map) {
    if( _map != NULL)
        free(_map);

    _width = width;
    _height = height;
    _map = (char*)malloc(sizeof(char) * width * height);
    memcpy(_map, map, width * height);
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
    free(tmp);
}
