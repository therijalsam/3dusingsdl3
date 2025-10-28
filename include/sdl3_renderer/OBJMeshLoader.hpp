#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include "Mesh.hpp"

namespace s3d {
    class OBJMeshLoader {
    public:
        Mesh load(const std::string& path) {
            Mesh mesh;
            std::ifstream file(path);
            if (!file.is_open()) return mesh;

            std::string line;
            while (std::getline(file, line)) {
                std::istringstream ss(line);
                std::string type;
                ss >> type;
                if (type == "v") {
                    float x, y, z;
                    ss >> x >> y >> z;
                    mesh.vertices.push_back({x, y, z});
                } else if (type == "f") {
                    int a, b, c;
                    ss >> a >> b >> c;
                    mesh.faces.push_back({a - 1, b - 1, c - 1});
                }
            }
            return mesh;
        }
    };
}
