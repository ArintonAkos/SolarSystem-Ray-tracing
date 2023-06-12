#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float orbitSpeed, float orbitAngle, float orbitRadius) : radius(1.0f)
{
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
}

Planet::~Planet() {}

float Planet::getRadius() const
{
	return radius * std::max(std::max(mScale.x, mScale.y), mScale.z);
}

void Planet::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;

	float newX = orbitRadius * cos(orbitAngle);
	float newZ = orbitRadius * sin(orbitAngle);

	setPosition(newX, 0, newZ);
}
