#include "player.h"

Player::Player(v2f coord, radian rotation, radian fov)
: _coord(coord), _rotation(rotation), _fov(fov) {}

void Player::forward() {
    _coord = _coord + velocity(_rotation);
}

void Player::backward() {
    _coord = _coord - velocity(_rotation);
}

void Player::left() {
    _coord = _coord + velocity(_rotation + PI/2);
}

void Player::right() {
    _coord = _coord - velocity(_rotation + PI/2);
}

void Player::turn(radian angle) {
    _rotation += angle;
}

v2f Player::velocity(radian angle) {
    return v2f{std::cos(angle), std::sin(angle)} / speed;
}
