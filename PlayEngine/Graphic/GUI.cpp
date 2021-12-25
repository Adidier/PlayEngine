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
		uniformProjection = shaderManager->GetCurrentShader()->GetUniformId("projection");
		uniformView = shaderManager->GetCurrentShader()->GetUniformId("view");

		unsigned int planeIndices[] = {			
			2, 3, 0,
			2, 1, 0,
		};

		std::vector<GLfloat> planeVertices = {
			//vector             and    uv
			-1.0f, -1.0f, -1.0f,        1,1, 
			 1.0f, -1.0f, -1.0f,        0,1,
			 1.0f, 1.0f, -1.0f,         0,0,
			-1.0f, 1.0f, -1.0f,         1,0
		};

		plane = new Mesh();
		plane->CreateMesh(planeVertices, planeIndices, 20, 6, 5);

		shaderManager->GetCurrentShader()->SetUniform("overlay", 0);
		//screenShader.setInt("screenTexture", 0);

		// framebuffer configuration
		// -------------------------

		glGenFramebuffers(1, &gbuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
		// create a color attachment texture
		
		glGenTextures(1, &textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1920, 1080, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
		// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
		unsigned int rbo;
		glGenRenderbuffers(1, &rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 1920, 1080); // use a single renderbuffer object for both a depth AND stencil buffer.
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
		// now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GUI::~GUI()
	{
		GUIOverlay* overlay = GUIOverlay::GetPtr();
		overlay->Remove(this);
	}

	void GUI::Draw()
	{
		//if (image != nullptr)
		//{
		//	image->Draw();
		//}

				// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDisable(GL_DEPTH_TEST); // disable depth test so screen-space quad isn't discarded due to depth test.
		// clear all relevant buffers
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
		glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
		glDrawArrays(GL_TRIANGLES, 0, 6);

		plane->RenderMesh();

		glBindFramebuffer(GL_FRAMEBUFFER, gbuffer);
		glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
	}
}
