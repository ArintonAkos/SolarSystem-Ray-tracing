#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius) : position(0.0f)
{
	this->radius = radius;
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
}

Planet::~Planet() {}

void Planet::setRadius(float radius)
{
	this->radius = radius;
}

float Planet::getRadius() const
{
	return radius;
}

glm::vec3 Planet::getPosition() const
{
	return position;
}

void Planet::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;

	position.x = orbitRadius * cos(orbitAngle);
	position.z = orbitRadius * sin(orbitAngle);
}
