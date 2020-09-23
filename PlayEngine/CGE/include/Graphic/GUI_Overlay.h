#pragma once
#include <list>
#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace Graphic
{
	class GUI_Overlay
	{
	private:
		std::list<class GUI*>* guis;
		GUI_Overlay();
		static GUI_Overlay* ptr;
	public:
		static GUI_Overlay* GetPtr();
		void Draw();
		void Add(class GUI*);
		void Remove(class GUI*);
	};
}