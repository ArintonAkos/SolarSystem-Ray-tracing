#include <GL/glew.h>
#include "Mesh.h"

Mesh::Mesh(const std::vector<DataTypes::Vertex> &vertices, const std::vector<uint32_t> &indices,
	const std::vector<DataTypes::Texture> &textures)
	: vertices(vertices), indices(indices), textures(textures), vertexArrayObject(0), vertexBufferObject(0), elementBufferObject(0)
{
	setup_mesh();
}

Mesh::~Mesh()
{
	destroy();
}

void Mesh::destroy()
{
    if (vertexArrayObject > 0)
    {
        glDeleteVertexArrays(1, &vertexArrayObject);
    }
    
    if (vertexBufferObject > 0)
    {
        glDeleteBuffers(1, &vertexBufferObject);
    }

    if (elementBufferObject > 0)
    {
        glDeleteBuffers(1, &elementBufferObject);
    }
}

void Mesh::setup_mesh()
{
    if (vertexArrayObject > 0 || vertexBufferObject > 0 || elementBufferObject > 0) 
    {
        destroy();
    }

    glGenVertexArrays(1, &vertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);
    glGenBuffers(1, &elementBufferObject);

    glBindVertexArray(vertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(DataTypes::Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t),
        &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(DataTypes::Vertex), (void*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(DataTypes::Vertex), (void*)offsetof(DataTypes::Vertex, normal));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(DataTypes::Vertex), (void*)offsetof(DataTypes::Vertex, texCoords));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::set_vertices(const std::vector<DataTypes::Vertex>& vertices)
{
	this->vertices = vertices;
}

void Mesh::set_indices(const std::vector<uint32_t>& indices)
{
	this->indices = indices;
}

void Mesh::set_textures(const std::vector<DataTypes::Texture>& textures)
{
	this->textures = textures;
}