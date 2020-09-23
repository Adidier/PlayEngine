#include "..\include\Graphic\GUI.h"
#include "Graphic/GUI_Overlay.h"
#include <glm.hpp>

namespace Graphic
{
	GUI::GUI(GUI_IMAGE* m_image, Camera* camera, ShaderManager* shaderManager): image(m_image), cameraToDraw(camera), sm(shaderManager)
	{
		GUI_Overlay* overlay = GUI_Overlay::GetPtr();
		overlay->Add(this);
		uniformProjection = shaderManager->GetUniformId("projection");
		uniformView = shaderManager->GetUniformId("view");

		unsigned int planeIndices[] = {
			2, 1, 0,
			2, 3, 0,
		};

		std::vector<GLfloat> planeVertices = {
			0.0f, 0.0f, -1.0f,
			1.0f, 0.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			0.0f, 1.0f, -1.0f,
		};

		plane = new Mesh();
		plane->CreateMesh(planeVertices, planeIndices, 12, 6, 3);
	}

	GUI::~GUI()
	{
		GUI_Overlay* overlay = GUI_Overlay::GetPtr();
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

		image->UseGUI_IMAGE(GL_TEXTURE0+100);
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
		plane->RenderMesh();
	}
}
