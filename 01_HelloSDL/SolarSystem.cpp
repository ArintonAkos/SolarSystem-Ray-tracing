#include "SolarSystem.h"


#include "Sun.h"

SolarSystem::SolarSystem()
{
    planetShader = new PlanetShader("planet.vert", "planet.frag");
    planetMesh = new PlanetMesh(1.0f, 50, 50);
    skyBox = new SolarSystemSkyBox();

    DataTypes::Material material;
    material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    material.shininess = 0.5f;

    DataTypes::Light light;
    light.position = glm::vec3(0, 0, 0);
    light.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;

    materials.push_back(material);
    lights.push_back(light);

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
    sun->attach_shader(planetShader);

    for (int i = 0; i < 8; ++i)
	{
        Planet* planet = new Planet(0.5f, (float)i, 10.0f + i * 10.0f);
		planet->attach_mesh(planetMesh);
		planet->attach_shader(planetShader);
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
    delete planetShader;
    delete sun;
    delete skyBox;
}

void SolarSystem::addPlanet(Planet* planet)
{
    planets.push_back(planet);
}

void SolarSystem::draw(Camera* camera)
{
    // skyBox->draw(camera);

    planetShader->setMat4("view", camera->getViewMatrix());
    planetShader->setMat4("projection", camera->getProjectionMatrix());

    planetShader->setCamera("camera", camera);
    
    planetShader->setLightArr("lights", lights);
    planetShader->setInt("lightCount", lights.size());

    planetShader->setMaterialArr("materials", materials);
    planetShader->setInt("materialCount", materials.size());

    planetShader->setPlanetArr("planets", planets);
    planetShader->setInt("planetCount", planets.size());

    planetMesh->set_texture_to_draw(TEXTURE_SUN);
    Shader* activeShader = sun->get_attached_shader();
    activeShader->setMat4("model", sun->getTransform());
    sun->draw();

    for (size_t i = 0; i < planets.size(); ++i)
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
