#include "Graphic/Model.h"

namespace Graphics {
	Model::Model()
	{
	}

	void Model::Draw()
	{

		GLuint uniformModel = 0;
		uniformModel = Base::ShaderManager::getPtr()->GetUniformId("model");
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(transform.GetTransform()));


		for (size_t i = 0; i < meshList.size(); i++)
		{
			for (size_t j = 0; j < textureList.size(); j++)
			{
				textureList[j]->UseTexture(GL_TEXTURE0 + j);
			}
			meshList[i]->RenderMesh();
		}
	}

	void Model::LoadModel(const std::string& fileName)
	{
		Assimp::Importer importer;
		const aiScene* scene = importer.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

		if (!scene)
		{
			printf("Model (%s) failed to load: %s", fileName, importer.GetErrorString());
			return;
		}

		LoadNode(scene->mRootNode, scene);

		LoadMaterials(scene);
	}

	void Model::LoadNode(aiNode* node, const aiScene* scene)
	{
		for (size_t i = 0; i < node->mNumMeshes; i++)
		{
			LoadMesh(scene->mMeshes[node->mMeshes[i]], scene);
		}

		for (size_t i = 0; i < node->mNumChildren; i++)
		{
			LoadNode(node->mChildren[i], scene);
		}
	}

	void Model::LoadMesh(aiMesh* mesh, const aiScene* scene)
	{
		std::vector<GLfloat> vertices;
		std::vector<unsigned int> indices;

		for (size_t i = 0; i < mesh->mNumVertices; i++)
		{
			vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
			if (mesh->mTextureCoords[0])
			{
				vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
			}
			else {
				vertices.insert(vertices.end(), { 0.0f, 0.0f });
			}
			vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
			vertices.insert(vertices.end(), { mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z });
		}

		for (size_t i = 0; i < mesh->mNumFaces; i++)
		{
			aiFace face = mesh->mFaces[i];
			for (size_t j = 0; j < face.mNumIndices; j++)
			{
				indices.push_back(face.mIndices[j]);
			}
		}

		Mesh* newMesh = new Mesh();
		newMesh->CreateMesh(vertices, &indices[0], vertices.size(), indices.size(), 11);
		meshList.push_back(newMesh);
		meshToTex.push_back(mesh->mMaterialIndex);
	}

	void Model::LoadMaterials(const aiScene* scene)
	{

		for (size_t i = 0; i < scene->mNumMaterials; i++)
		{
			aiMaterial* material = scene->mMaterials[i];


			if (material->GetTextureCount(aiTextureType_DIFFUSE))
			{
				aiString path;
				if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
				{
					AddTexture(path.C_Str());
				}
			}


		}
	}

	void Model::AddTexture(std::string path)
	{

		int idx = std::string(path).rfind("\\");
		std::string filename = std::string(path).substr(idx + 1);

		Graphic::Texture* texture;
		texture = new Graphic::Texture(filename.c_str());

		if (!texture->LoadTextureA())
		{
			printf("Failed to load texture at: %s\n", filename);
			delete texture;
			texture = nullptr;
			return;
		}
		textureList.push_back(texture);
	}

	void Model::ClearModel()
	{
		for (size_t i = 0; i < meshList.size(); i++)
		{
			if (meshList[i])
			{
				delete meshList[i];
				meshList[i] = nullptr;
			}
		}

		for (size_t i = 0; i < textureList.size(); i++)
		{
			if (textureList[i])
			{
				delete textureList[i];
				textureList[i] = nullptr;
			}
		}
	}

	Model::~Model()
	{
	}
}
