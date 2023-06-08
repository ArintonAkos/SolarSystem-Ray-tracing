#include "SpaceObject.h"
#include "Drawer.h"
#include "Camera.h"

void SpaceObject::draw(SDL_Renderer* renderer) {
	Drawer::DrawCircle(renderer, posX(), posY(), radius, color);
}

int SpaceObject::posX() {
	return x - camera->getView().x;
}

int SpaceObject::posY() {
	return x - camera->getView().y;
}