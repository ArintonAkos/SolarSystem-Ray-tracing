#pragma once

#include "Moveable.h";
#include "SpaceObject.h";
#include <glm/glm.hpp>

class Planet;

class Moon : public SpaceObject
{
private:
	glm::vec3 position;
	float radius;
	float orbitSpeed;
	float orbitAngle;
	float orbitRadius;
	float orbitTilt;

	Planet* parent;

public:
	Moon(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, Planet* parent, float orbitTilt = 0.0f);
	~Moon();

	void move(float deltaTime) override;
};