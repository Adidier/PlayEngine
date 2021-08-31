#include "Graphic/GUI_IMAGE.h"
#include"Base/ShaderManager.h"
#include "stb_image.h"

namespace Graphic
{
	GuiImage::GuiImage(const unsigned int handle, const std::string& name, const std::string& path) : IGUILayer(handle, name, path)
	{
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}


	bool GuiImage::ReadFile()
	{
		texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", path.c_str());
			return false;
		}
		return true;
	}

	Resource* GuiImage::Load()
	{
		auto sm = ShaderManager::getPtr();
		sm->Activate("gui");

		glGenTextures(1, &GUI_IMAGE_ID);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(texData);
		return this;
	}

	void GuiImage::Draw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);
	}

	void GuiImage::Clear()
	{
		glDeleteTextures(1, &GUI_IMAGE_ID);
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	GuiImage::~GuiImage()
	{
		Clear();
	}
}
