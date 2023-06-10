#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float orbitSpeed, float orbitAngle, float orbitRadius)
{
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
}

Planet::~Planet() {}

void Planet::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;

	float newX = orbitRadius * cos(orbitAngle);
	float newY = 0.0f;
	float newZ = orbitRadius * sin(orbitAngle);

	translate(newX, newY, newZ);
}
