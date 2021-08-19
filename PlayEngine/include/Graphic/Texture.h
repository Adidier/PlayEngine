
#ifndef  TEXTURE_H
#define  TEXTURE_H

#include "../Export.h"
#include "Base/Resource.h"
#define STB_IMAGE_IMPLEMENTATION
#include <GL\glew.h>
#include <string>
//#include "stb_image.h"
namespace Graphic
{
	typedef unsigned char stbi_uc;

	class PLAYENGINE Texture : public Resource
	{
	public:
		Texture(const unsigned int handle, const std::string& name, const std::string& path = "./");
		bool ReadFile() override;
		Resource* Load() override;
		void UseTexture(unsigned int i = 0);
		void ClearTexture();
		~Texture();
	private:
		stbi_uc *texData;
		GLuint textureID;
		int width, height, bitDepth;
	};

}
#endif // ! TEXTURE_H