#include "PlanetX.h";

PlanetX::PlanetX(std::vector<SpaceObject*> neighbours, int materialIndex, int textureIndex) : Planet(0.921f * 5.0f, 0.641f, 24.07f * 0.1f, 0.0f, 168.9f, 0.5f, materialIndex, textureIndex)
{
    this->neighbours = neighbours;
}

PlanetX::~PlanetX() {}

glm::vec3 PlanetX::get_movement_amount(SpaceObject* planet)
{
    float G = 6.67430e-11;
    glm::vec3 planetXPosition = get_position();

    glm::vec3 neighbourPosition = planet->get_position();
    float neighbourWeight = planet->get_weight();
    float neighbourDistance = glm::distance(neighbourPosition, planetXPosition);
    float neighbourGravitationalForce = (G * neighbourWeight * get_weight()) / (neighbourDistance * neighbourDistance);
    glm::vec3 neighbourDirection = glm::normalize(neighbourPosition - planetXPosition);
    glm::vec3 neighbourOrbitMovement = (neighbourGravitationalForce / get_weight()) * neighbourDirection;

    return neighbourOrbitMovement;
}

void PlanetX::move(float deltaTime)
{
    glm::vec3 totalMovement(0.0f);
    totalMovement += get_movement_amount(neighbours[0]);
    totalMovement += get_movement_amount(neighbours[1]);
    totalMovement += get_movement_amount(neighbours[2]);

    position.x += totalMovement.x;
    position.z += totalMovement.z;

	spinAngle += spinSpeed * deltaTime;
}