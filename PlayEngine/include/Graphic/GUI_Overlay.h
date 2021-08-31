#pragma once
#include <list>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Graphic
{
	class GUIOverlay
	{
	private:
		std::list<class GUI*>* guis;
		GUIOverlay();
		static GUIOverlay* ptr;
	public:
		static GUIOverlay* GetPtr();
		void Draw();
		void Add(class GUI*);
		void Remove(class GUI*);
	};
}