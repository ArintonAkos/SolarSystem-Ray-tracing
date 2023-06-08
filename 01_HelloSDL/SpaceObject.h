#pragma once
#include "Moveable.h"
#include <SDL.h>
#include "Camera.h"

class SpaceObject : public Movable {
protected:
    int x, y;  // position
    int radius; // size
    SDL_Color color; // color
    Camera* camera;

public:
    SpaceObject(int x, int y, int radius, SDL_Color color, Camera* camera) : x(x), y(y), radius(radius), color(color), camera(camera) {}

    virtual void draw(SDL_Renderer* renderer) override;

    int posX();

    int posY();
};