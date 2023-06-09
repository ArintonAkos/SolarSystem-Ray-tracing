#pragma once
#include "Moveable.h"
#include <SDL.h>
#include "Camera.h"

class SpaceObject : public Movable {
protected:
    Camera* camera;
    glm::vec3 position;

public:
    SpaceObject(Camera* camera, glm::vec3 position) : camera(camera), position(position) {};

    glm::vec3 getPosition() const;
};