#include "Graphic/GUI_IMAGE.h"
#include"Base/ShaderManager.h"
#include "stb_image.h"
//adidier cambiar los nombre de los archivos de gui
namespace Graphic
{
	ImageUI::ImageUI(const unsigned int counter, const std::string& name, const std::string& path) : IGUILayer(counter, name, path)
	{
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	bool ImageUI::ReadFile()
	{
		texData = stbi_load(path.c_str(), &width, &height, &bitDepth, 0);
		if (!texData)
		{
			printf("Failed to find: %s\n", path.c_str());
			return false;
		}
		return true;
	}

	Resource* ImageUI::Load()
	{
		auto sm = ShaderManager::GetPtr();
		sm->Activate("gui");//adidier llamar cada ciclo

		glGenTextures(1, &GUI_IMAGE_ID);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);//adidier quitar

		//glBindTexture(GL_TEXTURE_2D, 0);
		//stbi_image_free(texData);
		return this;
	}

	void ImageUI::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);
	}

	void ImageUI::Clear()
	{
		glDeleteTextures(1, &GUI_IMAGE_ID);
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	ImageUI::~ImageUI()
	{
		Clear();
	}
}
