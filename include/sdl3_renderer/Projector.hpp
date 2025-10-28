#pragma once
#include "IProjector.hpp"
#include <cmath>

namespace s3d {
    class PerspectiveProjector : public IProjector {
        float fov, aspect, nearPlane, farPlane;

    public:
        PerspectiveProjector(float fovDeg, float aspect, float n, float f)
            : fov(fovDeg), aspect(aspect), nearPlane(n), farPlane(f) {}

        Mat4 project(const Mat4& modelView) const override {
            float fovRad = 1.0f / tanf((fov * 0.5f) * (3.14159f / 180.0f));
            Mat4 proj;
            proj.m[0][0] = aspect * fovRad;
            proj.m[1][1] = fovRad;
            proj.m[2][2] = farPlane / (farPlane - nearPlane);
            proj.m[3][2] = (-farPlane * nearPlane) / (farPlane - nearPlane);
            proj.m[2][3] = 1.0f;
            proj.m[3][3] = 0.0f;
            return proj * modelView;
        }
    };
}
