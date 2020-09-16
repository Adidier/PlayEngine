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
			// front
			0, 1, 2,
			2, 1, 3,
		};

		std::vector<GLfloat> planeVertices = {
			-1.0f, 1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			1.0f, 1.0f, -1.0f,
			1.0f, -1.0f, -1.0f,
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

		sm->Activate("skybox");
		uniformView = sm->GetUniformId("view");
		viewMatrix = glm::mat4(glm::mat3(viewMatrix));
		sm->draw();
		glDepthMask(GL_TRUE);

		image->UseGUI_IMAGE(GL_TEXTURE0+100);

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		//glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(glm::mat4(1))); //Si usa esta se queda arriba la imagen
		plane->RenderMesh();
		glDepthMask(GL_TRUE);


	}
}
