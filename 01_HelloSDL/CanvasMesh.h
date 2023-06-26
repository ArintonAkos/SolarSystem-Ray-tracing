#pragma once

#include "Mesh.h"

class CanvasMesh : public Mesh
{
public:
	CanvasMesh();
	~CanvasMesh();

	void draw(Shader* shader) override;
};