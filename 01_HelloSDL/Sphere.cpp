#define _USE_MATH_DEFINES

#include "Sphere.h"
#include <cmath>
#include <math.h>

Sphere::Sphere(float radius, uint32_t rings, uint32_t sectors)
{
	float const R = 1.0f / (float)(rings - 1);
	float const S = 1.0f / (float)(sectors - 1);

	std::vector<DataTypes::Vertex> vertices(rings * sectors);
	std::vector<uint32_t> indices(rings * sectors * 6);
	std::vector<DataTypes::Vertex>::iterator v = vertices.begin();
	std::vector<uint32_t>::iterator i = indices.begin();

	for (uint32_t r = 0; r < rings; ++r)
	{
		for (uint32_t s = 0; s < sectors; ++s)
		{
			float const y = sin(-M_PI_2 + M_PI * r * R);
			float const x = cos(2 * M_PI * s * S) * sin(M_PI * r * R);
			float const z = sin(2 * M_PI * s * S) * sin(M_PI * r * R);

			v->position = glm::vec3(x, y, z) * radius;
			v->normal = glm::vec3(x, y, z);
			v->texCoords = glm::vec2(s * S, 1 - r * R);

			++v;
		}
	}

	for (uint32_t r = 0; r < rings - 1; ++r)
	{
		for (uint32_t s = 0; s < sectors - 1; ++s)
		{
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + s;
			*i++ = r * sectors + s;
			*i++ = (r + 1) * sectors + (s + 1);
		}
	}

	set_vertices(vertices);
	set_indices(indices);
	setup_mesh();
}
