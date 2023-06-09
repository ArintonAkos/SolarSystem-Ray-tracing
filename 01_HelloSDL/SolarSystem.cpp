#include "SolarSystem.h"
#include "Sun.h"

SolarSystem::SolarSystem(const std::string& sunTexturePath)
{
    DataTypes::Texture sunTexture{0, "", sunTexturePath };
    sun = new Sun(200.0f, sunTexture);
}

SolarSystem::~SolarSystem()
{
    for (auto planet : planets)
    {
        delete planet;
    }

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
