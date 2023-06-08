#pragma once
#include <SDL.h>
#include "SpaceObject.h"

class Planet : public SpaceObject {
private:
    int orbitRadius;
    double orbitSpeed;
    double orbitAngle;

public:
    Planet(int orbitRadius, double orbitSpeed, int radius, SDL_Color color, Camera* camera)
        : SpaceObject(0, 0, radius, color, camera), orbitRadius(orbitRadius), orbitSpeed(orbitSpeed), orbitAngle(0) {}

    void move() override;
};