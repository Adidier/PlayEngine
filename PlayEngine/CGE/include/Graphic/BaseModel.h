#ifndef MODEL_H
#define MODEL_H
#include "../Export.h"
#include "Mesh.h"
#include "Shader.h"
#include "Mesh.h"
#include "Camera.h"
#include<vector>
#include "../Base/Transform.h"

namespace Graphics {
	class PLAYENGINE BaseModel
	{
	public:
		BaseModel();
		virtual void Draw() = 0;
		void SetTransform(Base::Transform transform);
		Graphics::Mesh* GetMesh();
	protected:
		std::vector<Mesh*> meshList;
		Base::Transform transform;
		std::vector<GLfloat> vertices;

	};
}

#endif