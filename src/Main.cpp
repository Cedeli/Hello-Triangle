#include <iostream>
#include "gl_utils.hpp"

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello, Triangle!", NULL, NULL);
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

	// Triangle Data
	// -------------
	GLfloat vertices[] = {
		 0.5f,  0.5f, 0.0f,  // Top right
		 0.5f, -0.5f, 0.0f,  // Bottom right
		-0.5f, -0.5f, 0.0f,  // Bottom left
		-0.5f,  0.5f, 0.0f   // Top left 
	};

	GLuint indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	// Buffer Objects
	// --------------
	GLuint VBO;
	glCreateBuffers(1, &VBO);
	glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

	GLuint VAO;
	glCreateVertexArrays(1, &VAO);
	glVertexArrayAttribFormat(VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(VAO, 0, 0);
	glEnableVertexArrayAttrib(VAO, 0);

	GLuint EBO;
	glCreateBuffers(1, &EBO);
	glNamedBufferData(EBO, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 3);
	glVertexArrayElementBuffer(VAO, EBO);

	// Shader Initialization
	// --------------------
	GLuint vertexShader;
	GLchar* vertexSource;
	vertexSource = GLUtils::parseFileToString("src/shaders/triangle_shader.vert");
	GLUtils::createShader(&vertexShader, vertexSource, GL_VERTEX_SHADER);

	GLuint fragmentShader;
	GLchar* fragmentSource;
	fragmentSource = GLUtils::parseFileToString("src/shaders/triangle_shader.frag");
	GLUtils::createShader(&fragmentShader, fragmentSource, GL_FRAGMENT_SHADER);

	GLuint shaderProgram;
	GLUtils::createProgram(&shaderProgram, vertexShader, fragmentShader);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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
