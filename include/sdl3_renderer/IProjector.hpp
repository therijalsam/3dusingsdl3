#pragma once
#include "Mat4.hpp"

namespace s3d {
    class IProjector {
    public:
        virtual Mat4 project(const Mat4& modelView) const = 0;
        virtual ~IProjector() = default;
    };
}
