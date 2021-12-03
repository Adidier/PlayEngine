#pragma once
#include "../../Export.h"
#include <GL\glew.h>
#include <glm.hpp>

class PLAYENGINE Light
{
public:
	Light();
	Light(glm::vec3 ambientColor, glm::vec3 diffuseColor, glm::vec3 specularColor);
	~Light();
	virtual void UseLight() = 0;
protected:
	glm::vec3 ambientColor;
	glm::vec3 diffuseColor;
	glm::vec3 specularColor;
};
