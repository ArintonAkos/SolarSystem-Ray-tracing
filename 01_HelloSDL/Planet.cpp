#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, glm::vec3 position)
	: SpaceObject(position)
{
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
}

Planet::~Planet() {}

void Planet::move()
{
	orbitAngle += orbitSpeed;

	float newX = orbitRadius * cos(orbitAngle);
	float newY = 0.0f;
	float newZ = orbitRadius * sin(orbitAngle);

	position = glm::vec3(newX, newY, newZ);
}
