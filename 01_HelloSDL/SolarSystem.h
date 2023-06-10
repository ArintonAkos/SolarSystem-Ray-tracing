#pragma once

#include <vector>

#include "Planet.h"
#include "Sun.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class SolarSystem
{
private:
    Mesh* planetMesh;
    Shader* shader;

    Sun* sun;
    std::vector<Planet*> planets;

public:
    SolarSystem(const char* sunTexturePath);

    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update(float deltaTime);
};