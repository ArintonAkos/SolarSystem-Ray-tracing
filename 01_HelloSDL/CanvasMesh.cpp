#include "CanvasMesh.h"

#include <stdexcept>

CanvasMesh::CanvasMesh() : Mesh()
{
	std::vector<DataTypes::Vertex> verts(4);
	verts[0].position = glm::vec3(-1.0f, -1.0f, -1.0f);
	verts[1].position = glm::vec3(1.0f, -1.0f, -1.0f);
	verts[2].position = glm::vec3(1.0f, 1.0f, -1.0f);
	verts[3].position = glm::vec3(-1.0f, 1.0f, -1.0f);

	std::vector<uint32_t> inds = {
		0, 1, 2,
		2, 3, 0
	};

	set_vertices(verts);
	set_indices(inds);
	setup_mesh();
}

CanvasMesh::~CanvasMesh() {}

void CanvasMesh::draw(Shader* shader)
{
	shader->activate();

	glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}
