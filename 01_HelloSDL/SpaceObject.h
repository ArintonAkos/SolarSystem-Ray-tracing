#pragma once

#include "glm/glm.hpp"

class SpaceObject {
private:
    glm::mat4 transform;

public:
    SpaceObject() : transform(glm::mat4(1.0f)) {};

    void translate(float x, float y, float z);
    void rotate(float xAngle, float yAngle, float zAngle);
    void scale(float xScale, float yScale, float zScale);

    void setTransform(glm::mat4 transform);
    glm::mat4 getTransform() const;
};