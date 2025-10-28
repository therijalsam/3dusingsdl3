#pragma once
#include <SDL3/SDL.h>
#include "Mat4.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "IProjector.hpp"

namespace s3d {

    class Renderer3D {
        SDL_Renderer* sdlRenderer;
        const IProjector& projector;
        const Camera& camera;

    public:
        Renderer3D(SDL_Renderer* r, const IProjector& p, const Camera& c)
            : sdlRenderer(r), projector(p), camera(c) {}

        void drawMesh(const Mesh& mesh, const Mat4& model, int width, int height) const {
            Mat4 view = camera.getViewMatrix();
            Mat4 mvp = projector.project(view * model);

            SDL_SetRenderDrawColor(sdlRenderer, 255, 255, 255, 255);
            for (const auto& tri : mesh.faces) {
                Vec3 v0 = mvp.transformPoint(mesh.vertices[tri[0]]);
                Vec3 v1 = mvp.transformPoint(mesh.vertices[tri[1]]);
                Vec3 v2 = mvp.transformPoint(mesh.vertices[tri[2]]);

                auto sx = [&](float x) { return int((x * 0.5f + 0.5f) * width); };
                auto sy = [&](float y) { return int((-y * 0.5f + 0.5f) * height); };

                SDL_RenderLine(sdlRenderer, sx(v0.x), sy(v0.y), sx(v1.x), sy(v1.y));
                SDL_RenderLine(sdlRenderer, sx(v1.x), sy(v1.y), sx(v2.x), sy(v2.y));
                SDL_RenderLine(sdlRenderer, sx(v2.x), sy(v2.y), sx(v0.x), sy(v0.y));
            }
        }
    };
}
