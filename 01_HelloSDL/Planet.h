#pragma once
#include <SDL.h>
#include "SpaceObject.h"
#include "Sphere.h"
#include "Shader.h"

class Planet : public SpaceObject, public Sphere {
private:
    Shader* shader;
    DataTypes::Texture texture;
    
    float orbitSpeed;
    float orbitAngle;
    float orbitRadius;

public:
    Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, glm::vec3 position, DataTypes::Texture texture, Camera* camera);

    ~Planet();

    void move() override;

    void draw() override;
};