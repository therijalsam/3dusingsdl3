#pragma once
#include "Vec3.hpp"
#include "Mat4.hpp"
#include <algorithm>
#include <cmath>

namespace s3d {

    class Camera {
        Vec3 position;
        Vec3 target;
        Vec3 up;
        float distance;

    public:
        Camera()
            : position(0, 0, 5), target(0, 0, 0), up(0, 1, 0), distance(5.0f) {}

        // --- Camera Movements ---
        void moveForward(float delta) {
            Vec3 dir = (target - position).normalized();
            position += dir * delta;
            target += dir * delta;
        }

        void moveRight(float delta) {
            Vec3 dir = (target - position).normalized();
            Vec3 right = dir.cross(up).normalized();
            position += right * delta;
            target += right * delta;
        }

        void moveUp(float delta) {
            position.y += delta;
            target.y += delta;
        }

        // --- Orbit Rotation ---
        void orbit(float yaw, float pitch) {
            Vec3 dir = position - target;
            float radius = dir.length();
            float theta = atan2(dir.z, dir.x);
            float phi = acos(dir.y / radius);

            theta -= yaw;
            phi = std::clamp(phi - pitch, 0.1f, 3.13f);

            dir.x = radius * sin(phi) * cos(theta);
            dir.y = radius * cos(phi);
            dir.z = radius * sin(phi) * sin(theta);

            position = target + dir;
        }


        void zoom(float delta) {
            distance = std::clamp(distance + delta, 1.0f, 30.0f); // keep it safe
            Vec3 dir = (target - position).normalized();
            position = target - dir * distance;
        }

        Mat4 getViewMatrix() const {
            return Mat4::lookAt(position, target, up);
        }
    };

} // namespace s3d
