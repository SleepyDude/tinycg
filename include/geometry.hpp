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
    Vec3() : x(T()), y(T()), z(T()) {}
    Vec3(T x, T y, T z) : x(x), y(y), z(z) {}
    Vec3(Vec3 const &v) : x(v.x), y(v.y), z(v.z) {}
    template <class U> Vec3<T>(const Vec3<U> &v);
    Vec3 operator ^(Vec3 other) {
        T _x = y * other.z - z * other.y;
        T _y = - x * other.z + z * other.x;
        T _z = x * other.y - y * other.x;
        return {_x, _y, _z};
    }
    Vec3 operator -(Vec3 other) {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vec3 operator +(Vec3 other) {
        return {x + other.x, y + other.y, z + other.z};
    }
    void normalize() {
        T l = sqrt(x*x + y*y + z*z);
        x /= l;
        y /= l;
        z /= l;
    }
    T operator *(Vec3 other) {
        return x * other.x + y * other.y + z * other.z;
    }
    Vec3 operator *(float scale) {
        return {x*scale, y*scale, z*scale};
    }
};

typedef Vec3<float> Vec3f;
typedef Vec3<int>   Vec3i;
template <> template <> Vec3<int>::Vec3(const Vec3<float> &v);
template <> template <> Vec3<float>::Vec3(const Vec3<int> &v);

#endif // GEOMETRY_H
