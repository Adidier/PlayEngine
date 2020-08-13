#pragma once
#include "../../Export.h"
#include "Light.h"
namespace Graphics {
	namespace Lights {

		class PLAYENGINE DirectionalLight : public Light
		{
		public:
			DirectionalLight();
			DirectionalLight(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat xDir, GLfloat yDir, GLfloat zDir);

			void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
				GLfloat diffuseIntensityLocation, GLfloat directionLocation);

			~DirectionalLight();

		private:
			glm::vec3 direction;
		};
	}
}
