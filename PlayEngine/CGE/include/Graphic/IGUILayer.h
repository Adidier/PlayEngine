#pragma once
#include "../Export.h"
#include "Base/Resource.h"
#include "Base/Resource.h"
#include <GL\glew.h>
#include <string>

namespace Graphic
{
	class PLAYENGINE IGUILayer : public Resource
	{
	public:
		IGUILayer(const unsigned int handle, const std::string& name, const std::string& path = "./") :Resource(handle, name, path) {};
		virtual void Draw() = 0;
	};
}


