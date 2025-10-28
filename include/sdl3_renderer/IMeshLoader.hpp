#pragma once
#include <string>
#include "Mesh.hpp"

namespace s3d {

    class IMeshLoader {
    public:
        virtual ~IMeshLoader() = default;
        virtual Mesh load(const std::string& path) = 0;
    };

} // namespace s3d
