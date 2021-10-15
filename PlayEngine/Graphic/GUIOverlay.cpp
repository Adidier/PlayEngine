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
		auto sm = ShaderManager::getPtr(); //Adidier revisar salida de variables uniform
		glm::mat4 viewMatrix = sm->GetViewMatrix();
		glm::mat4 projectionMatrix = sm->GetProjectionMatrix();
		sm->Activate("gui");
		auto currentShader = sm->GetCurrentShader();
		viewMatrix = glm::mat4(1);
		sm->draw();

		glDepthMask(GL_FALSE);
		for (auto gui : *guis)
		{
			glEnable(GL_BLEND);//adidier falta envolver estas funciones de opengl
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			currentShader->SetUniform("view", viewMatrix);
			gui->Draw();
		}
		glDepthMask(GL_TRUE);
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

