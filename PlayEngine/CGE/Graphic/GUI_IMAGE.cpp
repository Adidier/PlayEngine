#include "Graphic/GUI_IMAGE.h"
#include "stb_image.h"

namespace Graphic
{
	GUI_IMAGE::GUI_IMAGE(const unsigned int handle, const std::string& name, const std::string& path) : Resource(handle, name, path)
	{
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}


	bool GUI_IMAGE::ReadFile()
	{
		texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", path.c_str());
			return false;
		}
	}

	Resource* GUI_IMAGE::Load()
	{
		glGenTextures(1, &GUI_IMAGE_ID);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(texData);
		return this;
	}

	void GUI_IMAGE::UseGUI_IMAGE(unsigned int i)
	{
		glActiveTexture(i);
		glBindTexture(GL_TEXTURE_CUBE_MAP, GUI_IMAGE_ID);
	}

	void GUI_IMAGE::ClearGUI_IMAGE()
	{
		glDeleteTextures(1, &GUI_IMAGE_ID);
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}


	GUI_IMAGE::~GUI_IMAGE()
	{
		ClearGUI_IMAGE();
	}
}
