#pragma once
#include <vector>
#include <array>
#include "Vec3.hpp"

namespace s3d {
    struct Mesh {
        std::vector<Vec3> vertices;
        std::vector<std::array<int, 3>> faces;

        bool isValid() const { return !vertices.empty() && !faces.empty(); }
    };
}
