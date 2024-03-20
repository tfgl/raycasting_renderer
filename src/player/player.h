#pragma once

#include "type.h"

class Player {
    void update_velocity();

public:
    enum MVT_DIR {UP, LEFT, DOWN, RIGHT};

    radian _rotation, _pitch = 0;
    radian _fov;
    v2f _coord;
    float _speed = 0.05;
    v2f _velocity;

    Player(v2f coord, radian rotation, radian fov);
    void forward();
    void backward();
    void left();
    void right();
    void turn(radian angle);
};
