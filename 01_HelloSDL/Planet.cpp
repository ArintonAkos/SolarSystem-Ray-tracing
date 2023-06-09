#include "Planet.h"
#include "DataTypes.h"
#include "Shader.h"

Planet::Planet(float radius, float orbitSpeed, float orbitAngle, float orbitRadius, glm::vec3 position, DataTypes::Texture texture, Camera* camera)
	: SpaceObject(camera, position), Sphere(radius, 50, 80)
{
	this->orbitSpeed = orbitSpeed;
	this->orbitAngle = orbitAngle;
	this->orbitRadius = orbitRadius;
	this->camera = camera;
    this->texture = texture;
    this->shader = new Shader("planet.vert", "planet.frag");
}

void Planet::move()
{
	orbitAngle += orbitSpeed;

	float newX = orbitRadius * cos(orbitAngle);
	float newY = 0.0f;
	float newZ = orbitRadius * sin(orbitAngle);

	position = glm::vec3(newX, newY, newZ);
}

void Planet::draw()
{
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;

    glActiveTexture(GL_TEXTURE0 + 0);

    std::string number;
    std::string name = texture.type;

    if (name == "texture_diffuse")
    {
        number = std::to_string(diffuseNr++);
    }
    else if (name == "texture_specular")
    {
        number = std::to_string(specularNr++);
    }

    // Ezt is
    // shader.setInt(name + number, i);
    glBindTexture(GL_TEXTURE_2D, texture.id);

    // TODO: @Bulcsu ezt nezd meg
    /*glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);*/

    glActiveTexture(GL_TEXTURE0);
}

Planet::~Planet()
{
    delete shader;
}