#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include "shader.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const GLuint WINDOW_WIDTH = 800;
const GLuint WINDOW_HEIGHT = 600;

int main()
{
	// GLFW: Initialization
	// --------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// GLFW: Window Creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hello, Triangle!", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window!";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	// GLAD: Initialization
	// --------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD!" << std::endl;
		return -1;
	}

	// Vertex Data
	// -------------
	GLfloat vertices[] = {
		 // Positions        // Colors			// Texture coords
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  0.5f, 1.0f
	};

	GLuint indices[] = {
		0, 1, 2
	};

	// Buffer Objects
	// --------------
	GLuint VAOBind = 0;
	GLuint posLayout = 0;
	GLuint colLayout = 1;
	GLuint texLayout = 2;

	GLuint VBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	
	// Position pointer
	glVertexArrayAttribFormat(VAO, posLayout, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(VAO, posLayout, VAOBind);
	glEnableVertexArrayAttrib(VAO, posLayout);

	// Color pointer
	glVertexArrayAttribFormat(VAO, colLayout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float));
	glVertexArrayAttribBinding(VAO, colLayout, VAOBind);
	glEnableVertexArrayAttrib(VAO, colLayout);

	// Texture pointer
	glVertexArrayAttribFormat(VAO, texLayout, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float));
	glVertexArrayAttribBinding(VAO, texLayout, VAOBind);
	glEnableVertexArrayAttrib(VAO, texLayout);

	GLuint EBO;
	glCreateBuffers(1, &EBO);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexArrayVertexBuffer(VAO, VAOBind, VBO, 0, 8 * sizeof(float));
	glVertexArrayElementBuffer(VAO, EBO);

	// Shader Initialization
	// ---------------------
	Shader triangleShader("src/shaders/triangle_shader.vert", "src/shaders/triangle_shader.frag");

	// Texture Initialization
	// ----------------------
	GLuint texture;
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load and generate the texture
	GLint width, height, nrChannels;
	unsigned char* data = stbi_load("resources/textures/wall.jpg", &width, &height, &nrChannels, 0);
	if (data)
	{
		// Allocate storage
		glTextureStorage2D(texture, 1, GL_RGB8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(texture);
	}
	else
	{
		std::cerr << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);

		triangleShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Wireframe Mode
// --------------
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) 
{
	if (key == GLFW_KEY_SPACE && action == GLFW_RELEASE)
	{
		GLint polygonMode;
		glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
		glPolygonMode(GL_FRONT_AND_BACK, polygonMode == GL_LINE ? GL_FILL : GL_LINE);
	}
}

void processInput(GLFWwindow* window) 
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}
