#ifndef HELLO_TRIANGLE_SHADER_H
#define HELLO_TRIANGLE_SHADER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	GLuint program;

	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);

	void use();
};

#endif
