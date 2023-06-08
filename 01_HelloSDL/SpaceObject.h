#pragma once
#include "Moveable.h"
#include <SDL.h>

class SpaceObject : public Movable {
protected:
    int x, y;  // position
    int radius; // size
    SDL_Color color; // color

public:
    SpaceObject(int x, int y, int radius, SDL_Color color) : x(x), y(y), radius(radius), color(color) {}

    virtual void draw(SDL_Renderer* renderer) override;
};