#pragma once
#include "../../Export.h"
#include <GL\glew.h>
#include <glm.hpp>

namespace Graphics {
	namespace Lights {
		class PLAYENGINE Light
		{
		public:
			Light();
			Light(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity);
			~Light();
		protected:
			glm::vec3 colour;
			GLfloat ambientIntensity;
			GLfloat diffuseIntensity;
		};
	}
}
