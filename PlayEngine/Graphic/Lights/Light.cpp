#include "Graphic/Lights/Light.h"

Light::Light()
{
	ambientColor = glm::vec3(1.0f, 1.0f, 1.0f);
	diffuseColor = glm::vec3(1.0f, 1.0f, 1.0f);
	specularColor = glm::vec3(1.0f, 1.0f, 1.0f);
}

Light::Light(glm::vec3 _ambientColor, glm::vec3 _diffuseColor, glm::vec3 _specularColor)
{
	ambientColor = _ambientColor;
	diffuseColor = _diffuseColor;
	specularColor = _specularColor;
}

Light::~Light()
{
}

