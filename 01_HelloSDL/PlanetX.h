#pragma once

#include "Planet.h"
#include "Planets.h"

#include <vector>

class PlanetX : public Planet
{
private:
	std::vector<SpaceObject*> neighbours;

	glm::vec3 get_movement_amount(SpaceObject* planet);
public:
	PlanetX(std::vector<SpaceObject*> neighbours, int materialIndex = 0, int textureIndex = -1);
	~PlanetX();

	void move(float deltaTime) override;
};