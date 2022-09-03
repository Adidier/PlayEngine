#include "Base/Transform.h"

Transform::Transform() : model(1)
{

}

void Transform::SetTranslation(float x, float y, float z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
}

void Transform::SetTranslation(glm::vec3 _translation)
{
	translation = _translation;
}

void Transform::SetRotation(glm::vec3 _rotation)
{
	rotation = glm::quat(glm::vec3(_rotation.x, _rotation.y, _rotation.z));
}

void Transform::SetRotation(float x, float y, float z)
{
	rotation = glm::quat(glm::vec3(x, y, z));
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
}

void Transform::SetScale(glm::vec3 _scale)
{
	scale = _scale;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}

glm::vec3 Transform::GetTranslation()
{
	return translation;
}

glm::mat4 Transform::GetTransform()
{
	model = glm::mat4(1.0);
	model = glm::translate(model, translation);
	model = glm::scale(model, scale);
	auto rot = glm::eulerAngles(rotation);
	model = glm::rotate(model, rot.x, glm::vec3(1, 0, 0));
	model = glm::rotate(model, rot.y, glm::vec3(0, 1, 0));
	model = glm::rotate(model, rot.z, glm::vec3(0, 0, 1));//TODO adidier mejorar la rotacion
	return model;
}
