#pragma once
#include "Sphere.h"
#include "Shader.h"

class Sun : public Sphere
{
private:
    Shader* shader;
    DataTypes::Texture texture;
    glm::vec3 position;

public:
    Sun(float radius, DataTypes::Texture texture);

    ~Sun();

    void draw() override;

    glm::vec3 getPosition() const;
};