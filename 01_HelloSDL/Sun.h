#pragma once

#include <glm/glm.hpp>
#include "SpaceObject.h"

class cSun : public SpaceObject
{
// private:
    // float weight;

public:
    cSun(float radius, float weight, int materialIndex, int textureIndex);
    ~cSun();

    // float get_weight() const;
    // void set_weight(float weight);
};