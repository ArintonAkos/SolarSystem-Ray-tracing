#include "Drawable.h"

#include <stdexcept>

Drawable::Drawable() : mesh(nullptr), shader(nullptr) {}

Drawable::Drawable(Mesh* mesh, Shader* shader) : mesh(mesh), shader(shader) {}

Drawable::~Drawable() {}

void Drawable::attach_mesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Drawable::attach_shader(Shader* shader)
{
	this->shader = shader;
}

void Drawable::draw()
{
	if (!mesh)
	{
		throw std::runtime_error("Mesh unavailable for drawing");
	}

	if (!shader)
	{
		throw std::runtime_error("Shader unavailable for drawing");
	}

	mesh->draw(shader);
}
