#include "PlanetX.h";

PlanetX::PlanetX(Planet* earth, Sun* sun, int materialIndex, int textureIndex) : Planet(0.921f * 5.0f, 0.641f, 24.07f * 0.1f, 0.0f, 168.9f, 0.5f, materialIndex, textureIndex) 
{
	this->earth = earth;
	this->sun = sun;
}

PlanetX::~PlanetX() {}

void PlanetX::move(float deltaTime)
{
	
}