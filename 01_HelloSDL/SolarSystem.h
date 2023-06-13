#pragma once

#include <vector>

#include "Planet.h"
#include "Sun.h"
#include "PlanetMesh.h"
#include "PlanetShader.h"
#include "Camera.h"
#include "DataTypes.h"
#include "SolarSystemSkyBox.h"

class SolarSystem
{
private:
    PlanetMesh* planetMesh;
    PlanetShader* planetShader;
    SolarSystemSkyBox* skyBox;

    std::vector<DataTypes::Material> materials;
    std::vector<DataTypes::Light> lights;

    Sun* sun;
    std::vector<Planet*> planets;

public:
    SolarSystem();
    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update(float deltaTime);
};