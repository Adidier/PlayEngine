#include "Graphic/Texture.h"
#include "stb_image.h"

namespace Graphic
{
	Texture::Texture(const unsigned int handle, const std::string& name, const std::string& path) : Resource(handle, name, path)
	{
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	bool Texture::ReadFile()
	{
		texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", path.c_str());
			return false;
		}
	}

	Resource* Texture::Load()
	{
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(texData);
		return this;
	}

	void Texture::UseTexture(unsigned int i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	void Texture::ClearTexture()
	{
		glDeleteTextures(1, &textureID);
		textureID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	Texture::~Texture()
	{
		ClearTexture();
	}
}