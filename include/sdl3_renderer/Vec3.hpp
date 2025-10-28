#pragma once
#include <cmath>

namespace s3d {

    struct Vec3 {
        float x, y, z;

        Vec3(float _x = 0, float _y = 0, float _z = 0)
            : x(_x), y(_y), z(_z) {}

        // --- Vector arithmetic ---
        Vec3 operator+(const Vec3& v) const { return {x + v.x, y + v.y, z + v.z}; }
        Vec3 operator-(const Vec3& v) const { return {x - v.x, y - v.y, z - v.z}; }
        Vec3 operator*(float s) const { return {x * s, y * s, z * s}; }
        Vec3 operator/(float s) const { return {x / s, y / s, z / s}; }

        Vec3& operator+=(const Vec3& v) { x += v.x; y += v.y; z += v.z; return *this; }
        Vec3& operator-=(const Vec3& v) { x -= v.x; y -= v.y; z -= v.z; return *this; }

        // --- Vector math ---
        float dot(const Vec3& v) const { return x * v.x + y * v.y + z * v.z; }

        Vec3 cross(const Vec3& v) const {
            return {
                y * v.z - z * v.y,
                z * v.x - x * v.z,
                x * v.y - y * v.x
            };
        }

        float length() const { return std::sqrt(x*x + y*y + z*z); }

        Vec3 normalized() const {
            float len = length();
            return (len > 1e-6f) ? *this / len : Vec3(0,0,0);
        }
    };

}
