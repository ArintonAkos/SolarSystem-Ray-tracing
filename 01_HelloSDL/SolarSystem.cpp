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
    material.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    material.diffuse = glm::vec3(0.2f, 0.2f, 0.2f);
    material.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    material.shininess = 7;

    DataTypes::Material mercuryMaterial;
    mercuryMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    mercuryMaterial.diffuse = glm::vec3(0.5703f, 0.5703f, 0.5429f);
    mercuryMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    mercuryMaterial.shininess = 7;

    DataTypes::Material venusMaterial;
    venusMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    venusMaterial.diffuse = glm::vec3(0.9648f, 0.4179f, 0.0f);
    venusMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    venusMaterial.shininess = 7;

    DataTypes::Material earthMaterial;  
    earthMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    earthMaterial.diffuse = glm::vec3(0.0f, 0.3984f, 1.0f);
    earthMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    earthMaterial.shininess = 7;

    DataTypes::Material marsMaterial;
    marsMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    marsMaterial.diffuse = glm::vec3(1.0f, 0.3686f, 0.0f);
    marsMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    marsMaterial.shininess = 7;

    DataTypes::Material jupiterMaterial;
    jupiterMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    jupiterMaterial.diffuse = glm::vec3(0.6835f, 0.5273f, 0.2890f);
    jupiterMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    jupiterMaterial.shininess = 7;

    DataTypes::Material saturnMaterial;
    saturnMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    saturnMaterial.diffuse = glm::vec3(0.9137f, 0.8549f, 0.4627f);
    saturnMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    saturnMaterial.shininess = 7;

    DataTypes::Material uranusMaterial;
    uranusMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    uranusMaterial.diffuse = glm::vec3(0.5098f, 0.9647f, 0.9333f);
    uranusMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    uranusMaterial.shininess = 7;

    DataTypes::Material neptuneMaterial;
    neptuneMaterial.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    neptuneMaterial.diffuse = glm::vec3(0.0f, 0.0f, 0.6117f);
    neptuneMaterial.specular = glm::vec3(0.3f, 0.3f, 0.3f);
    neptuneMaterial.shininess = 7;

    DataTypes::Light light1;
    light1.position = glm::vec3(0.0f, 0.0f, 0.0f);
    light1.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    light1.diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
    light1.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light1.constant = 1.0f;
    light1.linear = 0.09f;
    light1.quadratic = 0.032f;

    DataTypes::Light light2;
    light2.position = glm::vec3(0.1f, 0.1f, 0.1f);
    light2.ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    light2.diffuse = glm::vec3(0.3f, 0.3f, 0.3f);
    light2.specular = glm::vec3(0.9f, 0.9f, 0.9f);
    light2.constant = 1.0f;
    light2.linear = 0.09f;
    light2.quadratic = 0.032f;

    materials.push_back(material);
    materials.push_back(mercuryMaterial);
    materials.push_back(venusMaterial);
    materials.push_back(earthMaterial);
    materials.push_back(marsMaterial);
    materials.push_back(jupiterMaterial);
    materials.push_back(saturnMaterial);
    materials.push_back(uranusMaterial);
    materials.push_back(neptuneMaterial);

    lights.push_back(light1);
    lights.push_back(light2);

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

    for (int i = 1; i < planets.size(); ++i)
    {
        for (const auto& moon : ((Planet*)planets[i])->get_moons())
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

