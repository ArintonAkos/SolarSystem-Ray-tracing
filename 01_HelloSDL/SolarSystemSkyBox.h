#pragma once

#include "SkyBox.h"
#include "Shader.h"
#include "CubeMesh.h"
#include "Camera.h"

class SolarSystemSkyBox : public SkyBox
{
public:
	SolarSystemSkyBox();

	void draw(const Camera* camera);
};