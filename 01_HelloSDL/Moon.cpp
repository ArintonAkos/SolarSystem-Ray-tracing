#include "Moon.h"
#include "Planet.h"

Moon::Moon(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, Planet* parent, float orbitTilt, float weight) : 
	SpaceObject(glm::vec3(0.0f), radius, parent->get_material_index(), orbitSpeed, orbitAngle, orbitRadius, 0.0f)
{
	this->radius = radius;
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
	this->parent = parent;
	this->orbitTilt = orbitTilt;
	this->weight = weight;
}

Moon::~Moon() {}

float Moon::get_weight() const
{
	return weight;
}

void Moon::set_weight(float weight)
{
	this->weight = weight;
}

void Moon::move(float deltaTime)
{
	SpaceObject::move(deltaTime);
	const glm::vec3 parentPosition = parent->get_position();

	position.x += parentPosition.x;
	position.y = parentPosition.y + orbitTilt * orbitRadius * sin(2 * orbitAngle);
	position.z += parentPosition.z;
}