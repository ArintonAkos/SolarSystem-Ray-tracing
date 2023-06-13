#pragma once

#include "Shader.h"
#include "Planet.h"
#include "Camera.h"

class PlanetShader : public Shader
{
public:
	PlanetShader(const char* vertexShaderSource, const char* fragmentShaderSource);
	~PlanetShader();

	void setPlanet(const std::string& name, Planet* planet, int materialIndex) const;
	void setCamera(const std::string& name, Camera* camera) const;
	
	void setPlanetArr(const std::string& name, std::vector<Planet*> planets) const;
};