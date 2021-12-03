//#include "Graphic/Model.h"
//#include "Base/ResourceManager.h"
//#include <filesystem>
//
//namespace Graphic 
//{
//	Model::Model(const std::string& name, const std::string& path) :
//		BaseModel(),
//		Resource(0, name, path)
//	{
//		maxDistance = std::numeric_limits<float>::min();
//	}
//
//	void Model::Draw()
//	{
//		auto currentShader = ShaderManager::getPtr()->GetCurrentShader();
//		currentShader->SetUniform("model", transform.GetTransform());
//		for (size_t i = 0; i < meshList.size(); i++)
//		{
//			for (size_t j = 0; j < textureList.size(); j++)
//			{
//				textureList[j]->UseTexture(j);
//			}
//			meshList[i]->RenderMesh();
//		}
//	}
//
//	bool Model::ReadFile()
//	{
//		const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);
//
//		if (!scene)
//		{
//			printf("Model (%s) failed to load: %s", path, importer.GetErrorString());
//			return false;
//		}
//		return true;
//	}
//
//	Resource* Model::Load()
//	{
//		const aiScene* scene = importer.GetScene();
//
//		LoadNode(scene->mRootNode, scene);
//
//		LoadMaterials(scene);
//
//		return this;
//	}
//
//	void Model::LoadNode(aiNode * node, const aiScene * scene)
//	{
//		node->mTransformation.Rotation;
//		node->mTransformation.Translation;
//
//		for (size_t i = 0; i < node->mNumMeshes; i++)
//		{
//			LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
//		}
//
//		for (size_t i = 0; i < node->mNumChildren; i++)
//		{
//			LoadNode(node->mChildren[i], scene);
//		}
//	}
//
//	glm::vec3 Model::GetCenterMesh(aiMesh* mesh)
//	{
//		glm::vec3 center(0,0,0);
//
//		for (size_t i = 0; i < mesh->mNumVertices; i++)
//		{
//			center += glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//		}
//		center /= mesh->mNumVertices;
//		return center;
//	}
//
//	glm::vec3 Model::GetCenter()
//	{
//		return center;
//	}
//
//	glm::vec3 Model::GetCorner()
//	{
//		return corner;
//	}
//
//	glm::vec3 Model::GetCornerMesh(aiMesh* mesh, glm::vec3 center)
//	{
//		for (size_t i = 0; i < mesh->mNumVertices; i++)
//		{
//			float x = (mesh->mVertices[i].x - center.x);
//			float y = (mesh->mVertices[i].y - center.y);
//			float z = (mesh->mVertices[i].z - center.z);
//			float dis = sqrt(x * x + y * y + z * z);
//			if (maxDistance < dis)
//			{
//				maxDistance = dis;
//				maxVector = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
//			}
//		}		
//		return maxVector;
//	}
//
//	void Model::LoadMesh(aiMesh * mesh, const aiScene * scene)
//	{
//		std::vector<GLfloat> vertices;
//		std::vector<unsigned int> indices;
//
//		center = GetCenterMesh(mesh);
//		corner = GetCornerMesh(mesh, center);
//
//		for (size_t i = 0; i < mesh->mNumVertices; i++)
//		{
//			vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
//			if (mesh->mTextureCoords[0])
//			{
//				vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
//			}
//			else {
//				vertices.insert(vertices.end(), { 0.0f, 0.0f });
//			}
//			vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
//			vertices.insert(vertices.end(), { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z });
//		}
//
//		for (size_t i = 0; i < mesh->mNumFaces; i++)
//		{
//			aiFace face = mesh->mFaces[i];
//			for (size_t j = 0; j < face.mNumIndices; j++)
//			{
//				indices.push_back(face.mIndices[j]);
//			}
//		}
//		Mesh* newMesh = new Mesh();
//		newMesh->CreateMesh(vertices, &indices[0], vertices.size(), indices.size(),11);
//		meshList.push_back(newMesh);
//		meshToTex.push_back(mesh->mMaterialIndex);
//	}
//
//	void Model::LoadMaterials(const aiScene * scene)
//	{
//		for (size_t i = 0; i < scene->mNumMaterials; i++)
//		{
//			aiMaterial* material = scene->mMaterials[i];
//			
//			if (material->GetTextureCount(aiTextureType_DIFFUSE))
//			{
//				aiString path;
//				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
//				{
//					AddTexture(path.C_Str());
//				}
//			}
//		}
//	}
//
//	float Model::GetMaxDistance()
//	{
//		return maxDistance;
//	}
//
//	void Model::AddTexture(std::string filename)
//	{
//		Graphic::Texture* texture = (Graphic::Texture*)ResourceManager::GetPtr()->GetElement(filename);
//		textureList.push_back(texture);
//	}
//
//	void Model::ClearModel()
//	{
//		for (size_t i = 0; i < meshList.size(); i++)
//		{
//			if (meshList[i])
//			{
//				delete meshList[i];
//				meshList[i] = nullptr;
//			}
//		}
//
//		for (size_t i = 0; i < textureList.size(); i++)
//		{
//			if (textureList[i])
//			{
//				delete textureList[i];
//				textureList[i] = nullptr;
//			}
//		}
//	}
//
//	Model::~Model()
//	{
//	}
//}