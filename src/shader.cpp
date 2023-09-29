#include "shader.hpp"

Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	std::string vertexSource;
	std::string fragmentSource;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try 
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexSource = vShaderStream.str();
		fragmentSource = fShaderStream.str();
	}
	catch (std::ifstream::failure e) 
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
	}

	const GLchar* vShaderSource = vertexSource.c_str();
	const GLchar* fShaderSource = fragmentSource.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderSource, NULL);
	glCompileShader(vertex);

	compileStatus(vertex, GL_VERTEX_SHADER);

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderSource, NULL);
	glCompileShader(fragment);

	compileStatus(fragment, GL_FRAGMENT_SHADER);

	program = glCreateProgram();
	glAttachShader(program, vertex);
	glAttachShader(program, fragment);
	glLinkProgram(program);

	compileStatus(program, GL_PROGRAM);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), (int)value);
}
void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}
void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

bool Shader::compileStatus(GLuint target, GLenum type)
{
	GLint success;
	GLchar infoLog[512];
	const GLchar* shaderType;

	if (type == GL_VERTEX_SHADER)
	{
		shaderType = "VERTEX";
	}
	else if (type == GL_FRAGMENT_SHADER)
	{
		shaderType = "FRAGMENT";
	}
	else if (type == GL_PROGRAM)
	{
		shaderType = "PROGRAM";
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(target, 512, NULL, infoLog);
			std::cerr << "ERROR::SHADER::" << shaderType << "::LINKING_FAILED\n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
	else
	{
		return false;
	}

	glGetShaderiv(target, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(target, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::" << shaderType << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return false;
	}

	return true;
}
