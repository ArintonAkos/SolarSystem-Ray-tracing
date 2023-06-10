#include "PlanetMesh.h"

#include <stdexcept>

PlanetMesh::PlanetMesh(float radius, uint32_t rings, uint32_t sectors) : Sphere(radius, rings, sectors) 
{
	textureToDraw = -1;
}

PlanetMesh::~PlanetMesh() {}

void PlanetMesh::set_texture_to_draw(int32_t textureToDraw)
{
	this->textureToDraw = textureToDraw;
}

void PlanetMesh::draw(Shader* shader)
{
	if (textureToDraw < 0 || textureToDraw >= textures.size())
	{
		throw std::runtime_error("Invalid texture selected");
	}

	shader->activate();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[textureToDraw].id);

	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
