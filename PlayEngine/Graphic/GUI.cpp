#include "..\include\Graphic\GUI.h"
#include "Graphic/GUI_Overlay.h"
#include <glm.hpp>

namespace Graphic
{
	//TODO revisar todo
	GUI::GUI(IGUILayer* m_image, Camera* camera, ShaderManager* shaderManager): image(m_image), cameraToDraw(camera), sm(shaderManager)
	{
		GUIOverlay* overlay = GUIOverlay::GetPtr();
		overlay->Add(this);
		uniformProjection = shaderManager->GetUniformId("projection");
		uniformView = shaderManager->GetUniformId("view");

		unsigned int planeIndices[] = {
			
			2, 3, 0,
			2, 1, 0,
		};

		std::vector<GLfloat> planeVertices = {
			-1.0f, -1.0f, -1.0f,1,1,
			1.0f, -1.0f, -1.0f,0,1,
			1.0f, 1.0f, -1.0f,0,0,
			-1.0f, 1.0f, -1.0f,1,0
		};

		plane = new Mesh();
		plane->CreateMesh(planeVertices, planeIndices, 20, 6, 5);
	}

	GUI::~GUI()
	{
		GUIOverlay* overlay = GUIOverlay::GetPtr();
		overlay->Remove(this);
	}

	void GUI::Draw()
	{
		glm::mat4 viewMatrix = sm->GetViewMatrix(); glm::mat4 projectionMatrix = sm->GetProjectionMatrix();

		sm->Activate("gui");
		uniformView = sm->GetUniformId("view");
		viewMatrix = glm::mat4(1);
		sm->draw();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		image->Draw();
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
		plane->RenderMesh();
	}
}
