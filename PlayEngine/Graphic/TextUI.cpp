#include "Graphic/TextUI.h"
#include"Base/ShaderManager.h"
#include "stb_image.h"
#include"SDL_ttf.h"
#include"SDL.h"

namespace Graphic
{
	TextUI::TextUI(const unsigned int counter, const std::string& name, const std::string& path) : IGUILayer(counter, name, path)
	{
		GUI_IMAGE_ID = 0;
		width = 1024;
		height = 1024;
		bitDepth = 4;
	
	}


	bool TextUI::ReadFile()
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

	void TextUI::PutPixel(GLubyte* buffer, const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
	{
		int offset = (x + (y * width)) * bitDepth;
		if (offset < 0 || offset > width * height * bitDepth)
			return;

		buffer[offset] = R;
		buffer[offset + 1] = G;
		buffer[offset + 2] = B;
		buffer[offset + 3] = A;

	}

	void TextUI::PutPixel(const int& x, const int& y, const char& R, const char& G, const char& B, const char& A)
	{
		PutPixel(Buffer, x, y, R, G, B, A);
	}

	Resource* TextUI::Load()
	{
		ShaderManager::getPtr()->Activate("gui");
		TTF_Init();
		getText();
		return this;
	}

	void TextUI::Draw()
	{
		
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);
		
	}

	void TextUI::Clear()
	{
		glDeleteTextures(1, &GUI_IMAGE_ID);
		GUI_IMAGE_ID = 0;
		width = 0;
		height = 0;
		bitDepth = 0;
	}
	
	void TextUI::Update() {
		//Rodrigo Eguiza
		//Checar la Update de la GUI ya que una vez cargados los archivos no logre sustituirlos para que el texto fuera modificable
		getText();
		

	}
	void TextUI::getText() {
		
		texto = "texto prueba";
		//Rodrigo Eguiza
		//std::getline(std::cin, texto, '\n'); //debido a que se requiere cargar los elementos a la tarjeta de video se quito esta opcion.
		TTF_Font* fuente;
		const char* pathc = path.c_str();
		SDL_Color color = { 255,255,255,255 };

		fuente = TTF_OpenFont(path.c_str(), 12);
		SDL_Surface* dataImage = TTF_RenderText_Blended(fuente, texto.c_str(), color);
		int size = dataImage->w * dataImage->h * dataImage->format->BytesPerPixel;
		pixels = new unsigned char[size];
		memcpy(pixels, dataImage->pixels, dataImage->pitch * dataImage->h);


		texData = pixels;
		width = dataImage->w;
		height = dataImage->h;


		glGenTextures(1, &GUI_IMAGE_ID);
		glBindTexture(GL_TEXTURE_2D, GUI_IMAGE_ID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
		glGenerateMipmap(GL_TEXTURE_2D);
		//Rodrigo Eguiza
		//Checar como dibujar en una parte de la pantalla ya que se dibuja sobre toda la pantalla

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glBindTexture(GL_TEXTURE_2D, 0);
		SDL_FreeSurface(dataImage);

	}

	TextUI::~TextUI()
	{
		Clear();
	}
	
}
