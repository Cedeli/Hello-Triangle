#ifndef HELLO_TRIANGLE_GL_UTILS_H
#define HELLO_TRIANGLE_GL_UTILS_H

#include <fstream>
#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class GLUtils {
public:
	GLUtils();
	~GLUtils();

	static GLchar* parseFileToString(const GLchar* filePath);
	static bool createShader(GLuint* shader, const GLchar* shaderSource, GLenum shaderType);
	static bool createProgram(GLuint* program, GLuint vert, GLuint frag);
};

#endif 
