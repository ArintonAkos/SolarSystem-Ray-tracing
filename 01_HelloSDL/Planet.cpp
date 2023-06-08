#include "Planet.h"

void Planet::move() {
	orbitAngle += orbitSpeed;

	x = orbitRadius * cos(orbitAngle);
	y = orbitRadius * sin(orbitAngle);
}