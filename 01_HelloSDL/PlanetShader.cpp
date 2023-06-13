#include "PlanetShader.h"

PlanetShader::PlanetShader(const char* vertexShaderSource, const char* fragmentShaderSource) : Shader(vertexShaderSource, fragmentShaderSource) {}

PlanetShader::~PlanetShader() {}

void PlanetShader::setPlanet(const std::string& name, Planet* planet, int materialIndex) const
{
	setVec3(name + ".position", planet->getPosition());
	setFloat(name + ".radius", planet->getRadius());
	setInt(name + ".materialIndex", materialIndex);
}

void PlanetShader::setCamera(const std::string& name, Camera* camera) const
{
	setVec3(name + ".position", camera->getEyePosition());

	setVec3(name + ".frontAxis", camera->getForwardDirection());
	setVec3(name + ".upAxis", camera->getUpDirection());
	setVec3(name + ".sideAxis", camera->getSideDirection());

	setFloat(name + ".fov", camera->getFOV());
	setFloat(name + ".width", camera->getWidth());
	setFloat(name + ".height", camera->getHeight());
}

void PlanetShader::setPlanetArr(const std::string& name, std::vector<Planet*> planets) const
{
	for (size_t i = 0; i < planets.size(); i++)
	{
		std::string varName = name + "[" + std::to_string(i) + "]";
		setPlanet(varName, planets[i], 0); // TODO: material index
	}
}
