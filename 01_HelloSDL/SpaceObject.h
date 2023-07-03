#pragma once

#include "Moveable.h"
#include <glm/glm.hpp>

class SpaceObject : public Movable
{
protected:
	glm::vec3 position;
	float weight = 0.0f;
	float radius;
	float spinSpeed;
	float spinAngle;
	int materialIndex;
	int textureIndex;

public:
	SpaceObject(glm::vec3 position, float radius, int materialIndex, float orbitSpeed, float orbitAngle, float orbitRadius, float spinSpeed, int textureIndex = -1);

	void set_position(glm::vec3 position);
	glm::vec3 get_position() const;

	void set_radius(float radius);
	float get_radius() const;

	void set_material_index(int materialIndex);
	int get_material_index() const;

	void set_texture_index(int textureIndex);
	int get_texture_index() const;

	void set_orbit_speed(float orbitSpeed);
	float get_orbit_speed() const;

	void set_orbit_angle(float orbitAngle);
	float get_orbit_angle() const;

	void set_weight(float weight);
	float get_weight() const;

	float get_spin_angle() const;

	void move(float deltaTime) override;
};