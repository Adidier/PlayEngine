#pragma once
#include "../../Export.h"
#include "Light.h"
namespace Graphics {
	namespace Lights {

		class PLAYENGINE PointLight :
			public Light
		{
		public:
			PointLight();
			PointLight(GLfloat red, GLfloat green, GLfloat blue,
				GLfloat aIntensity, GLfloat dIntensity,
				GLfloat xPos, GLfloat yPos, GLfloat zPos,
				GLfloat con, GLfloat lin, GLfloat exp);

			void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColourLocation,
				GLfloat diffuseIntensityLocation, GLfloat positionLocation,
				GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

			~PointLight();

		private:
			glm::vec3 position;

			GLfloat constant, linear, exponent;
		};
	}
}

