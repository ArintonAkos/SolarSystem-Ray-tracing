#include "Sun.h"

cSun::cSun(float radius, float weight, int materialIndex, int textureIndex) : 
	SpaceObject(glm::vec3(0.0f), radius, materialIndex, 0.0f, 0.0f, 0.0f, textureIndex) {}

cSun::~cSun() {}

float cSun::get_weight() const
{
	return weight;
}

void cSun::set_weight(float weight)
{
	this->weight = weight;
}