#ifndef HELLO_TRIANGLE_TEXTURE
#define HELLO_TRIANGLE_TEXTURE

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <stb_image.h>

#include <iostream>

class Texture {
	GLuint texture;
public:
	Texture(const GLchar* texturePath);

	GLuint const getTexture();
};

#endif

