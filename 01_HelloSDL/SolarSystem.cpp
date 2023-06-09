#include "SolarSystem.h"

#include "Sun.h"
#include "Sphere.h"

SolarSystem::SolarSystem(const char* sunTexturePath)
{
    shader = new Shader("default.vert", "default.frag");
    planetMesh = new Sphere(40, 50, 50);

    GLuint sunTexture = Mesh::create_texture_from_file(sunTexturePath);
    planetMesh->add_texture(sunTexture);

    sun = new Sun();
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

void SolarSystem::draw()
{
    sun->draw();

    for (auto planet : planets)
    {
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

glm::vec3 SolarSystem::getLightDirection(const Planet& planet) const
{
    return glm::normalize(sun->getPosition() - planet.getPosition());
}
