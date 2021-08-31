#pragma once
#include "../Export.h"
#include <vector>
#include <string>

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

#include "Mesh.h"
#include "Texture.h"
#include "../Base/Transform.h"
#include "../Base/ShaderManager.h"
#include "BaseModel.h"

namespace Graphic
{
	class PLAYENGINE Model : public BaseModel , public Resource
	{
	public:
		Model(const std::string& name, const std::string& path = "./");

		virtual bool ReadFile() override;
		virtual Resource* Load() override;
		virtual void Draw() override;
		void ClearModel();
		~Model();
		void AddTexture(std::string path);
	private:

		void LoadNode(aiNode *node, const aiScene *scene);
		void LoadMesh(aiMesh *mesh, const aiScene *scene);
		void LoadMaterials(const aiScene *scene);

		std::vector<Graphic::Texture*> textureList;
		std::vector<Graphic::Texture*> textureNormalList;
		std::vector<unsigned int> meshToTex;
		Assimp::Importer importer;
		
	};

}