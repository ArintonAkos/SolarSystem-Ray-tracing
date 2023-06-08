#include "Camera.h"
#include <SDL.h>
#include <iostream>

int Camera::lastMouseX = 0;
int Camera::lastMouseY = 0;

void Camera::handleEvent(SDL_Event& e) {
    switch (e.type) {
    case SDL_KEYDOWN:
        switch (e.key.keysym.sym) {
        case SDLK_w: y -= moveSpeed; break;
        case SDLK_a: x -= moveSpeed; break;
        case SDLK_s: y += moveSpeed; break;
        case SDLK_d: x += moveSpeed; break;
        default: break;
        }
        break;

    case SDL_MOUSEMOTION:
        if (lastMouseX == 0 && lastMouseY == 0) {
            lastMouseX = e.motion.x;
            lastMouseY = e.motion.y;
        }
        else {
            int dx = e.motion.x - lastMouseX;
            int dy = e.motion.y - lastMouseY;

            x += dx;
            y += dy;

            lastMouseX = e.motion.x;
            lastMouseY = e.motion.y;
        }
        break;

    default: break;
    }
}

SDL_Rect Camera::getView() {
    SDL_Rect view = { x, y, 640, 480 };
    return view;
}