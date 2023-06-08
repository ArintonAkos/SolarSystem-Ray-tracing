#include "SpaceObject.h"
#include "Camera.h"

void SpaceObject::draw() {

}

int SpaceObject::posX() {
	return x - camera->getView().x;
}

int SpaceObject::posY() {
	return x - camera->getView().y;
}