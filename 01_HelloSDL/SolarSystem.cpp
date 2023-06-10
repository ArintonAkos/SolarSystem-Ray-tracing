#include "SolarSystem.h"

#include "Sun.h"

SolarSystem::SolarSystem()
{
    shader = new Shader("default.vert", "default.frag");
    planetMesh = new PlanetMesh(1.0f, 50, 50);

    GLuint sunTexture = Mesh::create_texture_from_file("Textures/sun.jpg");
    planetMesh->add_texture(sunTexture);

    sun = new Sun();
    sun->attach_mesh(planetMesh);
    sun->attach_shader(shader);
}

SolarSystem::~SolarSystem()
{
    for (auto& planet : planets)
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
    activeShader->setMat4("view", camera->getViewMatrix());
    activeShader->setMat4("projection", camera->getProjectionMatrix());

    planetMesh->set_texture_to_draw(TEXTURE_SUN);
    activeShader->setMat4("model", sun->getTransform());
    sun->draw();

    for (auto& planet : planets)
    {
        activeShader = planet->get_attached_shader();
        activeShader->setMat4("model", planet->getTransform());
        planet->draw();
    }
}

void SolarSystem::update(float deltaTime)
{
    for (auto& planet : planets)
    {
        planet->move(deltaTime);
    }
}
