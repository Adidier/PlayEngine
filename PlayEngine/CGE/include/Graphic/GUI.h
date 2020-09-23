#pragma once
#include "../Export.h"
#include "GUI_IMAGE.h"
#include "GUI_Overlay.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include"Graphic/Camera.h"
#include"Base/ShaderManager.h"
#include "Graphic/Mesh.h"
#include "Base/Transform.h"


namespace Graphic
{
	class PLAYENGINE GUI
	{
	private:
		GUI_IMAGE* image;
		Camera* cameraToDraw;
		ShaderManager* sm;
		GLuint uniformProjection, uniformView;
		bool active;
		Mesh* plane;
	public:
		GUI(GUI_IMAGE* m_image, Camera*, ShaderManager*);
		~GUI();
		void Draw();
	};
}


