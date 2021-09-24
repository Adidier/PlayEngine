#pragma once
#include "../Export.h"
#include "Base/Resource.h"
#include "Graphic/IGUILayer.h"
#include <GL\glew.h>
#include <string>

namespace Graphic
{
	typedef unsigned char stbi_uc;
	class PLAYENGINE TextUI : public IGUILayer
	{
	public:
		TextUI(const unsigned int handle, const std::string& name, const std::string& path = "./");
		bool ReadFile() override;
		Resource* Load() override;
		void Draw() override;
		void Clear();
		~TextUI();
		void PutPixel(GLubyte* buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);
		void PutPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);
		void Update();
		void getText();

	private:
		unsigned char Buffer[1024 * 1024 * 4];
		stbi_uc* texData;
		unsigned char* pixels;
		GLuint GUI_IMAGE_ID;
		int width, height, bitDepth;
		std::string texto = "texto prueba";
	};
}


