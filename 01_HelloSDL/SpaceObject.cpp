#include "SpaceObject.h"
#include "Camera.h"

void SpaceObject::translate(float x, float y, float z)
{
	transform = glm::translate(transform, glm::vec3(x, y, z));
}

void SpaceObject::rotate(float xAngle, float yAngle, float zAngle)
{
	transform = glm::rotate(transform, xAngle, glm::vec3(1, 0, 0));
	transform = glm::rotate(transform, yAngle, glm::vec3(0, 1, 0));
	transform = glm::rotate(transform, zAngle, glm::vec3(0, 0, 1));
}

void SpaceObject::scale(float xScale, float yScale, float zScale)
{
	transform = glm::scale(transform, glm::vec3(xScale, yScale, zScale));
}

void SpaceObject::setTransform(glm::mat4 transform)
{
	this->transform = transform;
}

glm::mat4 SpaceObject::getTransform() const
{
	return transform;
}