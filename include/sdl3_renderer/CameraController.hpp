#pragma once
#include <SDL3/SDL.h>
#include "Camera.hpp"

namespace s3d {

    class CameraController {
        Camera& camera;
        bool rotating = false;
        int lastX = 0, lastY = 0;

    public:
        explicit CameraController(Camera& cam) : camera(cam) {}

        void handleEvent(const SDL_Event& e) {

            if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN && e.button.button == SDL_BUTTON_LEFT) {
                rotating = true;
                lastX = e.button.x;
                lastY = e.button.y;
            }
            else if (e.type == SDL_EVENT_MOUSE_BUTTON_UP && e.button.button == SDL_BUTTON_LEFT) {
                rotating = false;
            }
            else if (e.type == SDL_EVENT_MOUSE_MOTION && rotating) {
                int dx = e.motion.x - lastX;
                int dy = e.motion.y - lastY;
                camera.orbit(dx * 0.005f, dy * 0.005f);
                lastX = e.motion.x;
                lastY = e.motion.y;
            }


            if (e.type == SDL_EVENT_MOUSE_WHEEL) {
                camera.zoom(-e.wheel.y * 0.3f);
            }


            if (e.type == SDL_EVENT_KEY_DOWN) {
                SDL_Keycode key = e.key.key;
                switch (key) {
                    case SDLK_W: camera.moveForward(0.3f); break;
                    case SDLK_S: camera.moveForward(-0.3f); break;
                    case SDLK_A: camera.moveRight(-0.3f); break;
                    case SDLK_D: camera.moveRight(0.3f); break;
                    case SDLK_Q: camera.moveUp(-0.3f); break;
                    case SDLK_E: camera.moveUp(0.3f); break;
                    default: break;
                }
            }
        }
    };

} // namespace s3d
