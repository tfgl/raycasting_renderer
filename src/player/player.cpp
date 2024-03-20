#include "player.h"

void rotate_v2f(v2f& v, radian angle) {
    v2f rot {std::cos(angle), std::sin(angle)};
    v = {
        v.x * rot.x - v.y * rot.y,
        rot.x * v.y + rot.y * v.x
    };
}

Player::Player(v2f coord, radian rotation, radian fov)
: _coord(coord), _rotation(rotation), _fov(fov) {
    update_velocity();
}

void Player::forward() {
    _coord = _coord + _velocity;
}

void Player::backward() {
    _coord = _coord - _velocity;
}

void Player::left() {
    _coord = _coord + v2f{-_velocity.y, _velocity.x};
}

void Player::right() {
    _coord = _coord - v2f{-_velocity.y, _velocity.x};
}

void Player::turn(radian angle) {
    _rotation += angle;
    update_velocity();
}

void Player::update_velocity() {
    _velocity = v2f{std::cos(_rotation), std::sin(_rotation)} * _speed;
}
