
#include "Graphic/BaseModel.h"
namespace Graphics {

	void BaseModel::SetTransform(Base::Transform _transform)
	{
		transform = _transform;
	}

	BaseModel::BaseModel()
	{
		//transform = nullptr;
	}

	Mesh* BaseModel::GetMesh()
	{
		return meshList[0];
	}
}