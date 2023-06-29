#include "SolarSystem.h"
#include "Planets.h"

SolarSystem::SolarSystem(std::vector<SpaceObject*> planets)
{
    canvasMesh = new CanvasMesh();
    sceneShader = new SceneShader("planet.vert", "planet.frag");

    canvas = new Canvas();
    canvas->attach_mesh(canvasMesh);
    canvas->attach_shader(sceneShader);

    DataTypes::Material material;
    material.ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    material.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    material.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    material.shininess = 0.5f;

    DataTypes::Light light;
    light.position = glm::vec3(0, 0, 0);
    light.ambient = glm::vec3(0.9f, 0.9f, 0.9f);
    light.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    light.specular = glm::vec3(1.0f, 1.0f, 1.0f);
    light.constant = 1.0f;
    light.linear = 0.09f;
    light.quadratic = 0.032f;

    materials.push_back(material);
    lights.push_back(light);

    sun = new Sun();
    this->planets = planets;

    addMoonsToSpaceObjects();
}

SolarSystem::~SolarSystem()
{
    for (auto& planet : planets)
    {
        delete planet;
    }

    delete canvas;
    delete canvasMesh;
    delete sceneShader;
    delete sun;
}

void SolarSystem::addPlanet(Planet* planet)
{
    planets.push_back(planet);
}

void SolarSystem::draw(Camera* camera)
{
    sceneShader->setCamera("camera", camera);
    
    sceneShader->setLightArr("lights", lights);
    sceneShader->setInt("lightCount", lights.size());
    
    sceneShader->setMaterialArr("materials", materials);
    sceneShader->setInt("materialCount", materials.size());

    sceneShader->setPlanetArr("planets", planets);
    sceneShader->setInt("planetCount", planets.size());

    canvas->allignToCamera(camera);

    sceneShader->setMat4("model", canvas->getTransform());
    sceneShader->setMat4("view", camera->getViewMatrix());
    sceneShader->setMat4("projection", camera->getProjectionMatrix());

    canvas->draw();
}

void SolarSystem::update(float deltaTime)
{
    for (auto& planet : planets)
    {
        planet->move(deltaTime);
    }
}

void SolarSystem::addMoonsToSpaceObjects()
{
    std::vector<SpaceObject*> moons;

    for (const auto& planet : planets)
    {
        for (const auto& moon : ((Planet*)planet)->get_moons())
        {
			moons.push_back(moon);
		}
	}

    for (const auto& moon : moons)
    {
        planets.push_back(moon);
    }
}