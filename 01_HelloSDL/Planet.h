#pragma once

#include "glm/glm.hpp"
#include "Moon.h"
#include "Moveable.h"
#include <vector>

class Planet : public Movable {
private:
    int materialIndex;
    glm::vec3 position;

    float radius;
    float weight;

    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

protected:
    std::vector<Moon*> moons;

public:
    Planet(float radius, float weight, float orbitSpeed, float orbitAngle, float orbitRadius, int materialIndex);
    ~Planet();

    void set_radius(float radius);

    float get_radius() const;

    float get_weight() const;

    glm::vec3 get_position() const;

    void add_moon(Moon* moon);

    int get_material_index() const;

    void move(float deltaTime) override;
};