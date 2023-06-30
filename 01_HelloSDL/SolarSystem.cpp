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
    material.ambient = glm::vec3(0.7f, 0.8f, 0.9f);
    material.diffuse = glm::vec3(0.2f, 0.4f, 0.6f);
    material.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    material.shininess = 0.5f;

    DataTypes::Light light1;
    light1.position = glm::vec3(0, 0, 0);
    light1.ambient = glm::vec3(0.8f, 0.9f, 0.9f);
    light1.diffuse = glm::vec3(0.4f, 0.6f, 0.6f);
    light1.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light1.constant = 1.0f;
    light1.linear = 0.09f;
    light1.quadratic = 0.032f;

    DataTypes::Light light2;
    light2.position = glm::vec3(0.1, 0.1, 0.1);
    light2.ambient = glm::vec3(0.8f, 0.9f, 0.9f);
    light2.diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    light2.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light2.constant = 1.0f;
    light2.linear = 0.09f;
    light2.quadratic = 0.032f;

    materials.push_back(material);
    lights.push_back(light1);
    lights.push_back(light2);

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
    sceneShader->setInt("maxDepth", maxDepth);

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

void SolarSystem::handleKeyUpEvent(const SDL_KeyboardEvent& key)
{
    switch (key.keysym.scancode)
    {
        case SDL_SCANCODE_N:
            if (maxDepth > 1)
                maxDepth--;
            break;

        case SDL_SCANCODE_M:
			if (maxDepth < 30)
				maxDepth++;
			break;
        default:
            break;
    }
}

