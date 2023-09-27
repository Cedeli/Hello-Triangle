#include "gl_utils.hpp"

GLUtils::GLUtils()
{
}

GLUtils::~GLUtils()
{
}

GLchar* GLUtils::parseFileToString(const GLchar* filePath)
{
	std::ifstream file(filePath, std::ios::binary);
	if (!file.is_open())
	{
		std::cerr << "Could not open shader file: " << filePath << std::endl;
		return nullptr;
	}

	file.seekg(0, std::ios::end);
	std::streampos fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	if (fileSize == 0)
	{
		std::cerr << "File is empty: " << filePath << std::endl;
		return nullptr;
	}

	GLchar* buffer = new GLchar[fileSize];
	if (!file.read(buffer, fileSize))
	{
		std::cerr << "Could not parse shader file: " << filePath << std::endl;
		delete[] buffer;
		return nullptr;
	}

	buffer[fileSize] = '\0';
	return buffer;
}

bool GLUtils::createShader(GLuint* shader, const GLchar* shaderSource, GLenum shaderType)
{
	*shader = glCreateShader(shaderType);
	glShaderSource(*shader, 1, &shaderSource, NULL);
	glCompileShader(*shader);

	int success;
	char infoLog[512];
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*shader, 512, NULL, infoLog);
		std::cerr << "Shader index " << *shader << " has failed to compile! " << infoLog << std::endl;
		return false;
	}
	return true;
}

bool GLUtils::createProgram(GLuint* program, GLuint vert, GLuint frag)
{
	*program = glCreateProgram();
	glAttachShader(*program, vert);
	glAttachShader(*program, frag);
	glLinkProgram(*program);

	int success;
	char infoLog[512];
	glGetProgramiv(*program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(*program, 512, NULL, infoLog);
		std::cerr << "Program index " << *program << " has failed to link! " << infoLog << std::endl;
		return false;
	}

	glDeleteShader(vert);
	glDeleteShader(frag);
	return true;
}
