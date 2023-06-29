#include "Moon.h"
#include "Planet.h"

Moon::Moon(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, Planet* parent, float orbitTilt)
	: position(0.0f)
{
	this->radius = radius;
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
	this->parent = parent;
	this->orbitTilt = orbitTilt;
}

Moon::~Moon() {}

void Moon::set_radius(float radius)
{
	this->radius = radius;
}

float Moon::get_radius() const
{
	return radius;
}

glm::vec3 Moon::get_position() const
{
	return position;
}

void Moon::move(float deltaTime)
{
	orbitAngle += orbitSpeed * deltaTime;
	const glm::vec3 parentPosition = parent->get_position();

	position.x = parentPosition.x + orbitRadius * cos(orbitAngle);
	position.y = parentPosition.y + orbitTilt * orbitRadius * sin(2 * orbitAngle);
	position.z = parentPosition.z + orbitRadius * sin(orbitAngle);
}