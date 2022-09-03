#pragma once
#include "../Export.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class PLAYENGINE Transform
{
public:
	void SetTranslation(float x, float y, float z);
	void SetTranslation(glm::vec3 translation);
	void SetRotation(float x, float y, float z);
	void SetRotation(glm::vec3 translation);
	void SetScale(float x, float y, float z);
	void SetScale(glm::vec3 translation);
	glm::vec3 GetScale();
	glm::vec3 GetTranslation();
	glm::mat4 GetTransform();
	Transform();
private:
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::mat4 model;
};
