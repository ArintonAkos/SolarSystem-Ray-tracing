#include "Sun.h"
#include "DataTypes.h"
#include <vector>

Sun::Sun(float radius, DataTypes::Texture texture) : Sphere(radius, 50, 80)
{
    this->texture = texture;
    this->shader = new Shader("sun.vert", "sun.frag");
    this->position = glm::vec3(0.0f, 0.0f, 0.0f);
}

Sun::~Sun()
{
    delete shader;
}

void Sun::draw()
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

glm::vec3 Sun::getPosition() const
{
	return position;
}