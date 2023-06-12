#include "SkyBox.h"
#include <vector>
#include <string>

SkyBox::SkyBox(const std::vector<std::string>& faces)
	: CubeMesh(get_vertices(), get_indices(), faces)
{
    shader = new Shader("skybox.vert", "skybox.frag");
}

SkyBox::~SkyBox()
{
    delete shader;
}

std::vector<float> SkyBox::get_vertices() const
{
    return 
    {
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        1.0f,  1.0f,  1.0f,
        1.0f, -1.0f,  1.0f
    };
}

std::vector<uint32_t> SkyBox::get_indices() const
{
    return 
    {
        // Front face
        0, 1, 3,
        1, 2, 3,
        // Right face
        2, 3, 6,
        2, 6, 7,
        // Back face
        7, 6, 5,
        7, 5, 4,
        // Left face
        4, 5, 0,
        5, 1, 0,
        // Bottom face
        1, 5, 2,
        5, 7, 2,
        // Top face
        6, 0, 3,
        6, 3, 4
    };
}