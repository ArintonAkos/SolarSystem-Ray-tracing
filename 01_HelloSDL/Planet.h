#pragma once

#include "glm/glm.hpp"
#include "Moon.h"
#include "Moveable.h"
#include "SpaceObject.h"
#include <vector>

class Planet : public SpaceObject {
private:
    float weight;

protected:
    std::vector<Moon*> moons;

public:
    Planet(float radius, float weight, float orbitSpeed, float orbitAngle, float orbitRadius, float spinSpeed, int materialIndex, int textureIndex);
    ~Planet();

    float get_weight() const;
    void set_weight(float weight);

    void add_moon(Moon* moon);

    std::vector<Moon*> Planet::get_moons() const;
};