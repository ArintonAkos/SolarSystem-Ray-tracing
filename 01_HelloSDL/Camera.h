#pragma once
#include <SDL.h>

class Camera {
private:
    int x, y;
    const int moveSpeed = 5;
    
    static int lastMouseX;
    static int lastMouseY;

public:
    Camera(int x, int y) : x(x), y(y) {}

    void handleEvent(SDL_Event& e);

    SDL_Rect getView();
};