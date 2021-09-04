#include "Graphic/BaseModel.h"

void BaseModel::SetTransform(Transform _transform)
{
	transform = _transform;
}

BaseModel::BaseModel()
{
}

Mesh* BaseModel::GetMesh()
{
	return meshList[0];
}