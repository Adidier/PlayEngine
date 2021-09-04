#pragma once
#include "../Export.h"

#include "Graphic/IGUILayer.h"
#include <GL\glew.h>
#include <string>

namespace Graphic
{
	typedef unsigned char stbi_uc;

	class PLAYENGINE ImageUI final : public IGUILayer
	{
	public:
		ImageUI(const unsigned int handle, const std::string& name, const std::string& path = "./");
		void Draw() override;
		bool ReadFile() override;
		Resource* Load() override;
		
		void Clear();
		~ImageUI();
	private:
		stbi_uc* texData;
		GLuint GUI_IMAGE_ID;
		int width, height, bitDepth;
	};
}


