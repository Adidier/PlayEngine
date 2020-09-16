#include "..\include\Graphic\GUI_Overlay.h"
#include "Graphic/GUI.h"

namespace Graphic
{
	GUI_Overlay* GUI_Overlay::ptr;

	GUI_Overlay::GUI_Overlay()
	{
		guis = new std::list<GUI*>();
	}

	GUI_Overlay* Graphic::GUI_Overlay::GetPtr()
	{
		if (ptr == nullptr)
		{
			ptr = new GUI_Overlay();
		}
		return ptr;
	}

	void GUI_Overlay::Draw()
	{
		//glDisable(GL_DEPTH_TEST);
		//glDisable(GL_CULL_FACE);
		//glDisable(GL_TEXTURE_2D);
		//glDisable(GL_LIGHTING);

		//glMatrixMode(GL_MODELVIEW);
		//glPushMatrix();
		//glLoadIdentity();
		//glOrtho(0.0, 800, 600, 1.0, -1.0, 1.0);
		//glEnable(GL_BLEND);
		//glEnable(GL_TEXTURE_2D);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//glMatrixMode(GL_MODELVIEW);
		//glLoadIdentity();
		//glColor3f(1, 1, 1);

		for (auto gui : *guis)
		{
			gui->Draw();
		}
	}

	void GUI_Overlay::Add(GUI* gui)
	{
		guis->push_back(gui);
	}
	void GUI_Overlay::Remove(GUI* gui)
	{
		guis->remove(gui);
	}
}

