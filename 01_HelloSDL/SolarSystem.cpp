#include "SolarSystem.h"

#include "Sun.h"
#include "Sphere.h"

SolarSystem::SolarSystem(const char* sunTexturePath)
{
    shader = new Shader("default.vert", "default.frag");
    planetMesh = new Sphere(1.0f, 50, 50);

    GLuint sunTexture = Mesh::create_texture_from_file(sunTexturePath);
    planetMesh->add_texture(sunTexture);

    sun = new Sun();
    sun->scale(0.011f, 0.011f, 0.011f);
    sun->attach_mesh(planetMesh);
    sun->attach_shader(shader);
}

SolarSystem::~SolarSystem()
{
    for (auto planet : planets)
    {
        delete planet;
    }

    delete planetMesh;
    delete shader;
    delete sun;
}

void SolarSystem::addPlanet(Planet* planet)
{
    planets.push_back(planet);
}

void SolarSystem::draw(Camera* camera)
{
    Shader* activeShader = sun->get_attached_shader();
    activeShader->setMat4("view", camera->GetViewMatrix());
    activeShader->setMat4("projection", camera->GetProjectionMatrix());

    activeShader->setMat4("model", sun->getTransform());
    sun->draw();

    for (auto planet : planets)
    {
        activeShader->setMat4("model", planet->getTransform());
        planet->draw();
    }
}

void SolarSystem::update()
{
    for (auto planet : planets)
    {
        planet->move();
    }
}
