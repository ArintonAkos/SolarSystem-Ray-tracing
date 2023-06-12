#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "CubeMesh.h"
#include <iostream>

CubeMesh::CubeMesh(const std::vector<float>& vertices, const std::vector<uint32_t>& indices, const std::vector<std::string>& faces)
	: vertices(vertices), indices(indices), faces(faces)
{
	setup_mesh();
	textureId = loadCubemap(faces);
}

CubeMesh::~CubeMesh()
{
	glDeleteTextures(1, &textureId);
	glDeleteVertexArrays(1, &vertexArrayObject);
	glDeleteBuffers(1, &vertexBufferObject);
	glDeleteBuffers(1, &elementBufferObject);
}

void CubeMesh::setup_mesh()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glGenBuffers(1, &vertexBufferObject);
	glGenBuffers(1, &elementBufferObject);

	glBindVertexArray(vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);
}

unsigned int CubeMesh::loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}


void CubeMesh::draw(Shader* shader, const Camera* camera)
{
	shader->activate();

	shader->setMat4("view", camera->getViewMatrix());
	shader->setMat4("projection", camera->getProjectionMatrix());

	glBindVertexArray(vertexArrayObject);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureId);
	glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}