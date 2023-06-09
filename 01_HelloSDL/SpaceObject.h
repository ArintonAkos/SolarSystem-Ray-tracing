#pragma once

#include "glm/glm.hpp"

class SpaceObject {
protected:
    glm::vec3 position;

public:
    SpaceObject() : position(glm::vec3(0.0f)) {};
    SpaceObject(glm::vec3 position) : position(position) {};

    glm::vec3 getPosition() const;
};