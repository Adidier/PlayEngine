//#pragma once
//#include "../Export.h"
//#include <vector>
//#include <string>
//
//#include <assimp\Importer.hpp>
//#include <assimp\scene.h>
//#include <assimp\postprocess.h>
//
//#include "Mesh.h"
//#include "Texture.h"
//#include "../Base/Transform.h"
//#include "../Base/ShaderManager.h"
//#include "BaseModel.h"
//#include <glm.hpp>
//#include <gtc\matrix_transform.hpp>
//#include <gtc\type_ptr.hpp>
//
//namespace Graphic
//{
//	class PLAYENGINE Model : public BaseModel , public Resource
//	{
//	public:
//		Model(const std::string& name, const std::string& path = "./");
//
//		virtual bool ReadFile() override;
//		virtual Resource* Load() override;
//		virtual void Draw() override;
//		void ClearModel();
//		~Model();
//		void AddTexture(std::string path);
//		float GetMaxDistance();
//		glm::vec3 GetCenter();
//		glm::vec3 GetCorner();
//
//		float maxDistance;
//	private:
//		glm::vec3 GetCenterMesh(aiMesh* mesh);
//		glm::vec3 GetCornerMesh(aiMesh* mesh, glm::vec3 center);
//		void LoadNode(aiNode *node, const aiScene *scene);
//		void LoadMesh(aiMesh *mesh, const aiScene *scene);
//		void LoadMaterials(const aiScene *scene);
//
//		std::vector<Graphic::Texture*> textureList;
//		std::vector<Graphic::Texture*> textureNormalList;
//		std::vector<unsigned int> meshToTex;
//		Assimp::Importer importer;
//
//		glm::vec3 maxVector;
//		glm::vec3 center;
//		glm::vec3 corner;
//	};
//
//}