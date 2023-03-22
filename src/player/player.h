#pragma once

#include "type.h"

class Player {
    v2f velocity(radian angle);

public:
    enum MVT_DIR {UP, LEFT, DOWN, RIGHT};

    radian _rotation;
    radian _fov;
    v2f _coord;
    float speed = 20;

    Player(v2f coord, radian rotation, radian fov);
    void forward();
    void backward();
    void left();
    void right();
    void turn(radian angle);
};
