#pragma once
#include <SDL.h>
#include "SpaceObject.h"

class Sun : public SpaceObject {
public:
    Sun(int x, int y, int radius, SDL_Color color) : SpaceObject(x, y, radius, color) {}

    void move() override {};
};