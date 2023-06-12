#pragma once

#include <vector>
#include <string>
#include "DataTypes.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"

class CubeMesh
{
private:
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	std::vector<std::string> faces;
	unsigned int textureId;

	uint32_t vertexArrayObject, vertexBufferObject, elementBufferObject;

	void setup_mesh();

	unsigned int loadCubemap(std::vector<std::string> faces);

public:
	CubeMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<std::string>& faces);

	~CubeMesh();

	virtual void draw(Shader* shader, const Camera* camera);
};