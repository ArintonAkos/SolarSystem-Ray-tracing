#pragma once
#include <vector>
#include <string>
#include "Planet.h"
#include "Sun.h"

class SolarSystem
{
private:
    std::vector<Planet*> planets;
    Sun* sun;

public:
    SolarSystem(const std::string& sunTexturePath);

    ~SolarSystem();

    void addPlanet(Planet* planet);

    void draw();

    void update();

    glm::vec3 getLightDirection(const Planet& planet) const;
};