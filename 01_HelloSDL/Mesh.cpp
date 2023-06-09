#include "Mesh.h"

#include <GL/glew.h>
#include <SDL_image.h>
#include <stdexcept>

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

    for (auto& texture : textures)
	{
        if (texture.id > 0) 
        {
            glDeleteTextures(1, &texture.id);
        }
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

void Mesh::add_texture(GLuint texture_id)
{
    DataTypes::Texture texture = { texture_id, "texture_diffuse" };

    textures.push_back(texture);
}

GLuint Mesh::create_texture_from_file(const char* texturePath)
{
    SDL_Surface* surface = IMG_Load(texturePath);
    int img_mode = 0;

    if (!surface) 
    {
        throw std::runtime_error("Failed to load texture");
    }

# if SDL_BYTEORDER == SDL_LIL_ENDIAN
    if (surface->format->BytesPerPixel == 4) 
        img_mode = GL_BGRA;
    else 
        img_mode = GL_BGR;
# else
    if (surface->format->BytesPerPixel == 4) 
		img_mode = GL_RGBA;
	else 
		img_mode = GL_RGB;
# endif

    GLuint texture_id = 0;
    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, surface->w, surface->h, img_mode, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(surface);

    return texture_id;
}

void Mesh::draw(Shader *shader)
{
    shader->activate();

    for (size_t i = 0; i < textures.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

    glBindVertexArray(vertexArrayObject);
	glDrawElements(GL_TRIANGLES, static_cast<uint32_t>(indices.size()), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}
