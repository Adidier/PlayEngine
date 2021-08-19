#include "..\include\Graphic\GUI_Overlay.h"
#include "Graphic/GUI.h"

namespace Graphic
{
	GUIOverlay* GUIOverlay::ptr;

	GUIOverlay::GUIOverlay()
	{
		guis = new std::list<GUI*>();
	}

	GUIOverlay* Graphic::GUIOverlay::GetPtr()
	{
		if (ptr == nullptr)
		{
			ptr = new GUIOverlay();
		}
		return ptr;
	}

	void GUIOverlay::Draw()
	{
		for (auto gui : *guis)
		{
			gui->Draw();
		}
	}

	void GUIOverlay::Add(GUI* gui)
	{
		guis->push_back(gui);
	}

	void GUIOverlay::Remove(GUI* gui)
	{
		guis->remove(gui);
	}
}

