#pragma once

#include <vector>
#include <ctime>

#include "Planet.h"
#include "Planets.h"
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
    std::vector<SpaceObject*> planets;

    int maxDepth = 5;

    void init_materials();
    void init_lights();

public:
    SolarSystem(std::vector<SpaceObject*> planets);
    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw(Camera* camera);

    void update(float deltaTime);

    void addMoonsToSpaceObjects();

    std::vector<SpaceObject*> get_planets();

    void handleKeyUpEvent(const SDL_KeyboardEvent& key);
};