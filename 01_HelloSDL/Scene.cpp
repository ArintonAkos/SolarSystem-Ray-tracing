#include "Scene.h"

#include <algorithm>

Scene::Scene(uint32_t nrPlanets)
{
	std::vector<Planet*> planets;
	planets.push_back(new Mercury());
	planets.push_back(new Venus());
	planets.push_back(new Earth());
	planets.push_back(new Mars());
	planets.push_back(new Jupiter());
	planets.push_back(new Saturn());
	planets.push_back(new Uranus());
	planets.push_back(new Neptune());

	if (nrPlanets == 8)
	{
		solarSystem = new SolarSystem(planets);
	}
	else
	{
		std::vector<Planet*> randomPlanets;
		std::vector<bool> usedIndexes(8, true);

		for (int i = 0; i < nrPlanets; i++)
		{
			int randomIndex = rand() % 8;

			if (usedIndexes[randomIndex])
			{
				randomPlanets.push_back(planets[randomIndex]);
				usedIndexes[randomIndex] = false;
			}
			else
			{
				i--;
			}
		}

		solarSystem = new SolarSystem(randomPlanets);
	}
}

Scene::~Scene()
{
	delete solarSystem;
}

void Scene::set_solar_system(SolarSystem* solarSystem)
{
	this->solarSystem = solarSystem;
}

SolarSystem* Scene::get_solar_system()
{
	return solarSystem;
}