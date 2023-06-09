#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

class Shader {
private:
	GLuint program_id;

	void check_for_errors(GLuint shader, std::string type);

public:
	Shader(const char *vertexShaderSource, const char *fragmentShaderSource);
	~Shader();

	GLuint getProgramID();

	void activate();

	void setVec3(const char* name, glm::vec3 value) const;
	void setVec3(const char* name, float x, float y, float z) const;
	void setMat4(const char* name, glm::mat4 value) const;
};