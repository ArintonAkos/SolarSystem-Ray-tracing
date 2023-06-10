#include "SolarSystem.h"

#include "Sun.h"

SolarSystem::SolarSystem()
{
    shader = new Shader("planet.vert", "planet.frag");
    planetMesh = new PlanetMesh(1.0f, 50, 50);

    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/sun.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/mercury.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/venus.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/earth.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/mars.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/jupiter.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/saturn.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/uranus.jpg"));
    planetMesh->add_texture(Mesh::create_texture_from_file("Textures/neptune.jpg"));

    sun = new Sun();
    sun->attach_mesh(planetMesh);
    sun->attach_shader(shader);

    for (int i = 0; i < 8; ++i)
	{
        Planet* planet = new Planet(0.5f, (float)i, 10.0f + i * 10.0f);
		planet->attach_mesh(planetMesh);
		planet->attach_shader(shader);
		planet->setScale(0.2f + i * 0.2f, 0.2f + i * 0.2f, 0.2f + i * 0.2f);
		addPlanet(planet);
	}
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
    activeShader->setVec3("light.position", 0, 0, 0);
    activeShader->setVec3("light.ambient", 0.2f, 0.2f, 0.2f);
    activeShader->setVec3("light.diffuse", 0.5f, 0.5f, 0.5f);
    activeShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);

    activeShader->setFloat("light.constant", 1.0f);
    activeShader->setFloat("light.linear", 0.09f);
    activeShader->setFloat("light.quadratic", 0.032f);

    planetMesh->set_texture_to_draw(TEXTURE_SUN);
    activeShader->setMat4("model", sun->getTransform());
    sun->draw();

    for (int i = 0; i < planets.size(); ++i)
    {
        planetMesh->set_texture_to_draw(i + 1);
        activeShader = planets[i]->get_attached_shader();
        activeShader->setMat4("model", planets[i]->getTransform());
        planets[i]->draw();
    }
}

void SolarSystem::update(float deltaTime)
{
    for (auto& planet : planets)
    {
        planet->move(deltaTime);
    }
}
