#pragma once
#include "../Export.h"
#include "IGUILayer.h"
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
		IGUILayer* image;
		Camera* cameraToDraw;
		ShaderManager* sm;
		GLuint uniformProjection, uniformView;
		bool active;
		Mesh* plane;
	public:
		GUI(IGUILayer* m_image, Camera*, ShaderManager*);
		~GUI();
		void Draw();

		//Rodrigo Eguiza
		//Agregar funcion Update para poder actualizar la GUI 
		/*Debido a que las Guis no tienen esta funcion no se puede hacer un llamado para actualizarlas
		*Por otra parte no se como se maneja los recursos en la memoria ya que una vez cargados no pueden ser actualizados o modificados
		*/

		virtual void Update();
	};
}


