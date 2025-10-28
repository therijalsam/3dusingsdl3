#include <SDL3/SDL.h>
#include <iostream>
#include "sdl3_renderer/Renderer3D.hpp"
#include "sdl3_renderer/OBJMeshLoader.hpp"
#include "sdl3_renderer/Projector.hpp"
#include "sdl3_renderer/Camera.hpp"
#include "sdl3_renderer/CameraController.hpp"
#include "sdl3_renderer/ModelTransformer.hpp"

using namespace s3d;

int main() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        std::cerr << "SDL init failed: " << SDL_GetError() << "\n";
        return 1;
    }

    const int WIDTH = 960, HEIGHT = 640;
    SDL_Window* window = SDL_CreateWindow("SDL3 3D Viewer", WIDTH, HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!window) {
        std::cerr << "Window creation failed.\n";
        return 1;
    }

    SDL_Renderer* sdlRenderer = SDL_CreateRenderer(window, nullptr);
    if (!sdlRenderer) {
        std::cerr << "Renderer creation failed.\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }


    Camera camera;
    CameraController camCtrl(camera);
    PerspectiveProjector projector(70.0f, float(WIDTH) / HEIGHT, 0.1f, 100.0f);
    Renderer3D renderer(sdlRenderer, projector, camera);


    OBJMeshLoader loader;
    Mesh mesh = loader.load("assets/cube.obj");
    if (!mesh.isValid()) {
        std::cerr << "Failed to load model.\n";
        return 1;
    }


    Mat4 model = ModelTransformer::computeTransform(mesh);


    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) running = false;
            camCtrl.handleEvent(e);
        }

        SDL_SetRenderDrawColor(sdlRenderer, 0, 0, 0, 255);
        SDL_RenderClear(sdlRenderer);


        renderer.drawMesh(mesh, model, WIDTH, HEIGHT);

        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(16);
    }

    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
