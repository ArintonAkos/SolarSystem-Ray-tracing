#pragma once

#include "Moveable.h"
#include "glm/glm.hpp"

class Planet : public Movable {
private:
    glm::vec3 position;

    float radius;

    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

public:
    Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius);
    ~Planet();

    void setRadius(float radius);

    float getRadius() const;
    glm::vec3 getPosition() const;

    void move(float deltaTime) override;
};