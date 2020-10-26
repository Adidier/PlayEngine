#include "Graphic/GUILine.h"
#include"Base/ShaderManager.h"
#include "stb_image.h"

namespace Graphic
{
	GUILine::GUILine(const unsigned int handle) : IGUILayer(handle, "Line", "line")
	{
		GUI_IMAGE_ID = 0;
		width = 1024;
		height = 1024;
		bitDepth = 4;
	}


	bool GUILine::ReadFile()
	{
		for (int i = 0; i < width * height * bitDepth; i += 4)
		{
			Buffer[i] = 255;
			Buffer[i + 1] = 255;
			Buffer[i + 2] = 255;
			Buffer[i + 3] = 255;
		}
		return true;
	}

	void GUILine::PutPixel(GLubyte* buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
	{
		int offset = (x + (y * width)) * bitDepth;
		if (offset < 0 || offset > width * height * bitDepth)
			return;

		buffer[offset] = R;
		buffer[offset + 1] = G;
		buffer[offset + 2] = B;
		buffer[offset + 3] = A;

		
	}

	void GUILine::PutPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
	{
		PutPixel(Buffer, x, y, R, G, B, A);
	}

	Resource* GUILine::Load()
	{
		ShaderManager::getPtr()->Activate("gui");

		if (GUI_IMAGE_ID == 0)
		{
			glGenTextures(1, &GUI_IMAGE_ID);
		}
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Buffer);
		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
		return this;
	}

	void GUILine::Draw()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);
	}

	void GUILine::Clear()
	{
		glDeleteTextures(1, &GUI_IMAGE_ID);
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}

	GUILine::~GUILine()
	{
		Clear();
	}
}
