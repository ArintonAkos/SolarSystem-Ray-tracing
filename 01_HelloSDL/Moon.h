#pragma once

#include "Moveable.h";
#include "SpaceObject.h";
#include <glm/glm.hpp>

class Planet;

class Moon : public SpaceObject
{
private:
	float orbitTilt;
	float weight;

	Planet* parent;

public:
	Moon(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, Planet* parent, float orbitTilt = 0.0f, float weight = 0.0077f);
	~Moon();

	float get_weight() const;
	void set_weight(float weight);

	void move(float deltaTime) override;
};