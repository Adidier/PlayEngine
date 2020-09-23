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

