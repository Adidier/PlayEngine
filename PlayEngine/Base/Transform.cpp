#include "Base/Transform.h"

Transform::Transform() : _model(1)
{

}

void Transform::SetTranslation(float x, float y, float z)
{
	_translation.x = x;
	_translation.y = y;
	_translation.z = z;
}

void Transform::SetRotation(float x, float y, float z)
{
	_rotation = glm::quat(glm::vec3(x, y, z));
}

void Transform::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}

glm::vec3 Transform::GetScale()
{
	return _scale;
}

glm::vec3 Transform::GetTranslation()
{
	return _translation;
}

glm::mat4 Transform::GetTransform()
{
	_model = glm::mat4(1.0);
	_model = glm::translate(_model, _translation);
	_model = glm::scale(_model, _scale);
	auto rotation = glm::eulerAngles(_rotation);
	_model = glm::rotate(_model, rotation.x, glm::vec3(1, 0, 0));
	_model = glm::rotate(_model, rotation.y, glm::vec3(0, 1, 0));
	_model = glm::rotate(_model, rotation.z, glm::vec3(0, 0, 1));//adidier mejorar la rotacion
	return _model;
}
