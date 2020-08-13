#ifndef SKYBOX_H
#define SKYBOX_H
#include "../Export.h"
#include <vector>
#include <string>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Mesh.h"
#include "Shader.h"
#include "../Base/ShaderManager.h"
namespace Graphics {
	class PLAYENGINE Skybox
	{
	public:
		Skybox(std::vector<std::string> faceLocations);
		void Draw(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);
		~Skybox();
	private:
		Mesh* skyMesh;
		GLuint textureId;
		GLuint uniformProjection, uniformView;
		Base::ShaderManager* shaderManager;
	};
}
#endif