#pragma once

#include "Sphere.h"

enum ePlanetTextures
{
	TEXTURE_SUN = 0,
	TEXTURE_MERCURY,
	TEXTURE_VENUS,
	TEXTURE_EARTH,
	TEXTURE_MARS,
	TEXTURE_JUPITER,
	TEXTURE_SATURN,
	TEXTURE_URANUS,
	TEXTURE_NEPTUNE
};

class PlanetMesh : public Sphere
{
private:
	int32_t textureToDraw;

public:
	PlanetMesh(float radius, uint32_t rings, uint32_t sectors);
	~PlanetMesh();

	void set_texture_to_draw(int32_t textureToDraw);

	void draw(Shader* shader) override;
};