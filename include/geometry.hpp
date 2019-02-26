#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <cmath>

template <typename T>
struct Vec2
{
    T x;
    T y;
    Vec2() : x(T()), y(T()) {}
    Vec2(T x, T y) : x(x), y(y) {}
    Vec2 operator *(float scale) {
        return {x*scale, y*scale};
    }
    Vec2 operator +(Vec2 other) {
        return {x + other.x, y + other.y};
    }
    Vec2 operator -(Vec2 other) {
        return {x - other.x, y - other.y};
    }
};

typedef Vec2<int>   Vec2i;
typedef Vec2<float> Vec2f;


template <typename T>
struct Vec3
{
    T x, y, z;
    Vec3 operator ^(Vec3 other) {
        T _x = y * other.z - z * other.y;
        T _y = - x * other.z + z * other.x;
        T _z = x * other.y - y * other.x;
        return {_x, _y, _z};
    }
    Vec3 operator -(Vec3 other) {
        return {x - other.x, y - other.y, z - other.z};
    }
    void normalize() {
        T l = sqrt(x*x + y*y + z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    float operator *(Vec3 other) {
        return x * other.x + y * other.y + z * other.z;
    }
};

typedef Vec3<float> Vec3f;


#endif // GEOMETRY_H
