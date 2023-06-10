#pragma once

#include "SpaceObject.h"
#include "Moveable.h"
#include "Drawable.h"

class Planet : public SpaceObject, public Movable, public Drawable {
private:
    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

public:
    Planet(float orbitSpeed, float orbitAngle, float orbitRadius);

    ~Planet();

    void move(float deltaTime) override;
};