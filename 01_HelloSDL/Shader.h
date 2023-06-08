#pragma once

#include <GL/glew.h>
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
};