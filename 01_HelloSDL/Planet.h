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
    Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, glm::vec3 position);

    ~Planet();

    void move() override;
};