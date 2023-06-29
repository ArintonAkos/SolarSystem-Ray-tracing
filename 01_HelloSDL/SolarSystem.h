#pragma once

#include <vector>
#include <ctime>

#include "Planet.h"
#include "Sun.h"
#include "CanvasMesh.h"
#include "SceneShader.h"
#include "Camera.h"
#include "Canvas.h"
#include "DataTypes.h"

class SolarSystem
{
private:
    CanvasMesh* canvasMesh;
    SceneShader* sceneShader;

    std::vector<DataTypes::Material> materials;
    std::vector<DataTypes::Light> lights;

    Canvas* canvas;

    Sun* sun;
    std::vector<Planet*> planets;

public:
    SolarSystem();
    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update(float deltaTime);
};