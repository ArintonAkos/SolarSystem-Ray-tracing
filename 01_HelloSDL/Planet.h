#pragma once

#include "SpaceObject.h"
#include "Moveable.h"
#include "Drawable.h"

class Planet : public SpaceObject, public Movable, public Drawable {
private:
    float radius;

    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

public:
    Planet(float orbitSpeed, float orbitAngle, float orbitRadius);
    ~Planet();

    float getRadius() const;

    void move(float deltaTime) override;
};