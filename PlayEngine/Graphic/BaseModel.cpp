#include "Graphic/BaseModel.h"

void BaseModel::SetTransform(Transform _transform)
{
	transform = _transform;
}

BaseModel::BaseModel(const std::string& name, const std::string& path)
{
}

Mesh* BaseModel::GetMesh()
{
	return meshList[0];
}