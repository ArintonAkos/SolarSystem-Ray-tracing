#pragma once

#include "Planet.h"
#include "Planets.h"

class PlanetX : public Planet
{
private:
	Planet* earth;
	Sun* sun;

public:
	PlanetX(Planet* earth, Sun* sun, int materialIndex = 0, int textureIndex = -1);
	~PlanetX();

	void move(float deltaTime) override;
};