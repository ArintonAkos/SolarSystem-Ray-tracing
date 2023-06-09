#pragma once

#include "Mesh.h"
#include "Shader.h"

class Drawable {
private:
    Mesh* mesh;
    Shader* shader;

public:
    Drawable();
    Drawable(Mesh *mesh, Shader *shader);
    ~Drawable();

    void attach_mesh(Mesh* mesh);
    void attach_shader(Shader* shader);

    void draw();
};
