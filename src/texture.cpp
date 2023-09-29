#include "texture.hpp"

Texture::Texture(const GLchar* texturePath)
{
	glCreateTextures(GL_TEXTURE_2D, 1, &texture);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTextureParameteri(texture, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTextureParameteri(texture, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(texture, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Load and generate the texture
	GLint width, height, nrChannels;
	unsigned char* data = stbi_load(texturePath, &width, &height, &nrChannels, 0);
	if (data)
	{
		// Allocate immutable storage
		glTextureStorage2D(texture, 1, GL_RGB8, width, height);
		glTextureSubImage2D(texture, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateTextureMipmap(texture);
	}
	else
	{
		std::cerr << "Failed to load texture!" << std::endl;
	}
	stbi_image_free(data);
}

GLuint const Texture::getTexture()
{
	return texture;
}
