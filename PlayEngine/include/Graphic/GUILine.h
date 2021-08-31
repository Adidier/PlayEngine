#pragma once
#include "../Export.h"
#include "Base/Resource.h"
#include "Graphic/IGUILayer.h"
#include <GL\glew.h>
#include <string>

namespace Graphic
{
	typedef unsigned char stbi_uc;
	class PLAYENGINE GUILine : public IGUILayer
	{
	public:
		GUILine(const unsigned int handle);
		bool ReadFile() override;
		Resource* Load() override;
		void Draw() override;
		void Clear();
		~GUILine();
		void PutPixel(GLubyte* buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);
		void PutPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A);

	private:
		unsigned char Buffer[1024 * 1024 * 4];
		GLuint GUI_IMAGE_ID;
		int width, height, bitDepth;
	};
}


