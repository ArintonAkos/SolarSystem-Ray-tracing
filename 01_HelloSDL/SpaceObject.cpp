#include "SpaceObject.h"

#include <glm/gtc/matrix_transform.hpp>

void SpaceObject::setPosition(float x, float y, float z)
{
	mPosition = glm::vec3(x, y, z);
}

void SpaceObject::setRotation(float xAngle, float yAngle, float zAngle)
{
	mRotation = glm::vec3(xAngle, yAngle, zAngle);
}

void SpaceObject::setScale(float xScale, float yScale, float zScale)
{
	mScale = glm::vec3(xScale, yScale, zScale);
}

void SpaceObject::translate(float x, float y, float z)
{
	mPosition += glm::vec3(x, y, z);
}

void SpaceObject::rotate(float xAngle, float yAngle, float zAngle)
{
	mRotation += glm::vec3(xAngle, yAngle, zAngle);
}

void SpaceObject::scale(float xScale, float yScale, float zScale)
{
	mScale = glm::vec3(mScale.x * xScale, mScale.y * yScale, mScale.z * zScale);
}

glm::vec3 SpaceObject::getPosition() const
{
	return mPosition;
}

glm::vec3 SpaceObject::getRotation() const
{
	return mRotation;
}

glm::vec3 SpaceObject::getScale() const
{
	return mScale;
}

glm::mat4 SpaceObject::getTransform() const
{
	glm::mat4 transform(1.0f);

	transform = glm::rotate(transform, mRotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, mRotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, mRotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	transform = glm::scale(transform, mScale);

	transform = glm::translate(transform, mPosition);

	return transform;
}