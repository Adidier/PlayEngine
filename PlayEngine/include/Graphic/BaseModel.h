#ifndef MODEL_H
#define MODEL_H
#include "../Export.h"
#include "Mesh.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include<vector>
#include "../Base/Transform.h"
#include "../Base/Resource.h"

class PLAYENGINE BaseModel 
{
public:
	BaseModel(const std::string& name, const std::string& path = "./");
	virtual void Draw() = 0;
	void SetTransform(Transform transform);
	Mesh* GetMesh();
protected:
	std::vector<Mesh*> meshList;
	Transform transform;
	std::vector<GLfloat> vertices;
};

#endif