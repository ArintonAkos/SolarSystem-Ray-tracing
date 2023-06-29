#include "Scene.h"

Scene::Scene()
{
	solarSystem = new SolarSystem();
}

Scene::~Scene()
{
	delete solarSystem;

	/*
	for (auto& planet : planets)
	{
		delete planet;
	}
	*/
}

void Scene::set_solar_system(SolarSystem* solarSystem)
{
	this->solarSystem = solarSystem;
}

SolarSystem* Scene::get_solar_system()
{
	return solarSystem;
}