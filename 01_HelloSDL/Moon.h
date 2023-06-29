#pragma once

#include "Moveable.h";
#include <glm/glm.hpp>

class Planet;

class Moon : Movable
{
public:
	Moon(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, Planet* parent, float orbitTilt = 0.0f);
	~Moon();

	void set_radius(float radius);
	float get_radius() const;
	glm::vec3 get_position() const;
	void move(float deltaTime);

private:
	glm::vec3 position;
	float radius;
	float orbitSpeed;
	float orbitAngle;
	float orbitRadius;
	float orbitTilt;

	Planet* parent;
};