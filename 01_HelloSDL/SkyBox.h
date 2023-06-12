#pragma once

#include "CubeMesh.h"
#include <vector>
#include <string>

class SkyBox : public CubeMesh
{
private:
	std::vector<float> get_vertices() const;

	std::vector<uint32_t> get_indices() const;

protected:
	Shader* shader;

public: 
	SkyBox(const std::vector<std::string>& faces);

	~SkyBox();
};