#pragma once

#include "Mesh.h"

class Sphere : public Mesh
{
public:
	Sphere(float radius, uint32_t rings, uint32_t sectors);
};