#pragma once

#include <vector>

#include "Planet.h"
#include "Sun.h"
#include "PlanetMesh.h"
#include "Shader.h"
#include "Camera.h"
#include "SolarSystemSkyBox.h"

class SolarSystem
{
private:
    PlanetMesh* planetMesh;
    Shader* shader;
    
    SolarSystemSkyBox* skyBox;
    Sun* sun;
    std::vector<Planet*> planets;

public:
    SolarSystem();
    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update(float deltaTime);
};