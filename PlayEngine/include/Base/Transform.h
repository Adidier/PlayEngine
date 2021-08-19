#pragma once
#include "../Export.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

class PLAYENGINE Transform
{
public:
	void SetTranslation(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	glm::vec3 GetTranslation();
	glm::mat4 GetTransform();
	Transform();
private:
	glm::vec3 _translation;
	glm::quat _rotation;
	glm::vec3 _scale;
	glm::mat4 _model;
};
