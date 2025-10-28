#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include "Camera.hpp"
#include "IProjector.hpp"
#include "Mat4.hpp"
#include "Vec3.hpp"

namespace s3d {

class GridRenderer {
    IProjector* projector;
    Camera& camera;
public:
    GridRenderer(IProjector* proj, Camera& cam) : projector(proj), camera(cam) {}

    void drawGround(SDL_Renderer* ren, int width, int height,
                    float yLevel = 0.0f, float size = 10.0f, int divisions = 20,
                    SDL_Color grid = {60,60,70,255},
                    SDL_Color xAxis = {200,60,60,255},
                    SDL_Color zAxis = {60,120,220,255}) const
    {
        Mat4 view = camera.getViewMatrix();

        auto projectWorld = [&](const Vec3& w)->Vec3{
            Vec3 cam = view.transformPoint(w);
            return projector->project(cam, width, height);
        };

        float step = size / divisions;
        float half = size * 0.5f;

        // Grid lines
        SDL_SetRenderDrawColor(ren, grid.r, grid.g, grid.b, grid.a);
        for (int i=0;i<=divisions;++i) {
            float t = -half + i*step;
            Vec3 p0 = projectWorld({-half, yLevel, t});
            Vec3 p1 = projectWorld({ half, yLevel, t});
            Vec3 p2 = projectWorld({ t, yLevel,-half});
            Vec3 p3 = projectWorld({ t, yLevel, half});
            if (!std::isnan(p0.x) && !std::isnan(p1.x)) SDL_RenderLine(ren, (int)p0.x,(int)p0.y, (int)p1.x,(int)p1.y);
            if (!std::isnan(p2.x) && !std::isnan(p3.x)) SDL_RenderLine(ren, (int)p2.x,(int)p2.y, (int)p3.x,(int)p3.y);
        }

        // Axes
        SDL_SetRenderDrawColor(ren, xAxis.r, xAxis.g, xAxis.b, xAxis.a);
        Vec3 x0 = projectWorld({-half, yLevel, 0});
        Vec3 x1 = projectWorld({ half, yLevel, 0});
        if (!std::isnan(x0.x) && !std::isnan(x1.x)) SDL_RenderLine(ren, (int)x0.x,(int)x0.y, (int)x1.x,(int)x1.y);

        SDL_SetRenderDrawColor(ren, zAxis.r, zAxis.g, zAxis.b, zAxis.a);
        Vec3 z0 = projectWorld({0, yLevel,-half});
        Vec3 z1 = projectWorld({0, yLevel, half});
        if (!std::isnan(z0.x) && !std::isnan(z1.x)) SDL_RenderLine(ren, (int)z0.x,(int)z0.y, (int)z1.x,(int)z1.y);
    }
};

} // namespace s3d
