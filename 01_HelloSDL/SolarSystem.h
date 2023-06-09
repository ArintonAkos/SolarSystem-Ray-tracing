#pragma once

#include <vector>

#include "Planet.h"
#include "Sun.h"
#include "Mesh.h"
#include "Shader.h"

class SolarSystem
{
private:
    Mesh* planetMesh;
    Shader* shader;

    std::vector<Planet*> planets;
    Sun* sun;

public:
    SolarSystem(const char* sunTexturePath);

    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw();

    void update();

    glm::vec3 getLightDirection(const Planet& planet) const;
};