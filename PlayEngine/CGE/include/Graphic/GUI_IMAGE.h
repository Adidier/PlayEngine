#pragma once
#include "../Export.h"
#include "Base/Resource.h"
#include <GL\glew.h>
#include <string>

namespace Graphic
{
	typedef unsigned char stbi_uc;
	class PLAYENGINE GUI_IMAGE : public Resource
	{
	public:
		GUI_IMAGE(const unsigned int handle, const std::string& name, const std::string& path = "./");
		bool ReadFile() override;
		Resource* Load() override;
		void UseGUI_IMAGE(unsigned int i = 0);
		void ClearGUI_IMAGE();
		~GUI_IMAGE();
	private:
		stbi_uc* texData;
		GLuint GUI_IMAGE_ID;
		int width, height, bitDepth;
	};
}


