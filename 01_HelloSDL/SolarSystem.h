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

    std::vector<Planet*> planets;
    Sun* sun;

public:
    SolarSystem(const char* sunTexturePath);

    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update();
};