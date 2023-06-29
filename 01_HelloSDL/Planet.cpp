#include "Planet.h"
#include "DataTypes.h"

Planet::Planet(float radius, float weight, float orbitSpeed, float orbitAngle, float orbitRadius, int materialIndex) : position(0.0f)
{
	this->radius = radius;
	this->weight = weight;
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
	this->materialIndex = materialIndex;
}

Planet::~Planet() {}

void Planet::set_radius(float radius)
{
	this->radius = radius;
}

float Planet::get_radius() const
{
	return radius;
}

float Planet::get_weight() const
{
	return weight;
}

glm::vec3 Planet::get_position() const
{
	return position;
}

void Planet::add_moon(Moon* moon)
{
	moons.push_back(moon);
}

int Planet::get_material_index() const
{
	return materialIndex;
}

void Planet::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;

	position.x = orbitRadius * cos(orbitAngle);
	position.z = orbitRadius * sin(orbitAngle);
}
