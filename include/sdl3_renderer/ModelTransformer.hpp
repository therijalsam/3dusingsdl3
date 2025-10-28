#pragma once
#include "Mesh.hpp"
#include "Mat4.hpp"
#include <algorithm>

namespace s3d {

    class ModelTransformer {
    public:
        static Mat4 computeTransform(const Mesh& mesh) {
            if (mesh.vertices.empty()) return Mat4::identity();

            Vec3 minV = mesh.vertices[0];
            Vec3 maxV = mesh.vertices[0];

            for (const auto& v : mesh.vertices) {
                minV.x = std::min(minV.x, v.x);
                minV.y = std::min(minV.y, v.y);
                minV.z = std::min(minV.z, v.z);
                maxV.x = std::max(maxV.x, v.x);
                maxV.y = std::max(maxV.y, v.y);
                maxV.z = std::max(maxV.z, v.z);
            }

            Vec3 center = (minV + maxV) * 0.5f;
            Vec3 size = maxV - minV;
            float maxExtent = std::max(std::max(size.x, size.y), size.z); // ✅ Fixed

            float scale = (maxExtent > 0.0f) ? (2.0f / maxExtent) : 1.0f;

            // Center at origin and scale down to fit the view
            return Mat4::scale(scale, scale, scale) * Mat4::translation(-center.x, -center.y, -center.z);
        }
    };

} // namespace s3d
