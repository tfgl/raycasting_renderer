#pragma once

#include <iostream>
#include <cmath>

template <class T>
struct v2 {
    T x, y;

    template<class U>
    v2<U> cast() const {
        return { (U)x, (U)y };
    }

    bool operator==(const v2& v) const {
        return x == v.x && y == v.y;
    }

    T mag() const {
        return std::sqrt( x*x + y*y );
    }

    v2 norm() const {
        return (*this)/mag();
    }

    T dot(const v2& v) const {
        return { x * v.x + y * v.y};
    }

    T cross(const v2& v) const {
        return { x * v.y - y * v.x};
    }

    v2 operator+(const v2& u) const {
        return v2{ x + u.x, y + u.y};
    }

    v2 operator-(const v2& u) const {
        return v2{ x - u.x, y - u.y};
    }

    v2 operator*(const v2& u) const {
        return { x * u.x, y * u.y};
    }

    v2 operator*(const T& s) const {
        return { x * s, y * s};
    }

    v2 operator/(const v2& u) const {
        return { x / u.x, y / u.y};
    }

    v2 operator/(const T& s) const {
        return { x / s, y / s};
    }

    friend std::ostream& operator<<(std::ostream& os, v2 v) {
        std::cout << "(" << v.x << ", " << v.y << ")";
        return os;
    }
};

using v2i = v2<int>;
using v2f = v2<float>;
