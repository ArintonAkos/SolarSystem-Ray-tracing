#pragma once

#include <vector>

#include "SolarSystem.h"
#include "Planet.h"

class Scene
{
private:
	SolarSystem* solarSystem;

public:
	Scene(uint32_t nrPlanets = 9);
	~Scene();

	void add_planet(Planet* planet);

	void set_solar_system(SolarSystem* solarSystem);
	
	SolarSystem* get_solar_system();
};