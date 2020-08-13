#pragma once
#include "../Export.h"
#include <GL\glew.h>
#include <vector>
#include "glm.hpp"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
namespace Graphics {
	class PLAYENGINE Mesh
	{
	public:
		Mesh();
		void CreateMesh(std::vector<GLfloat> vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vSize);
		void RenderMesh();
		void ClearMesh();
		const std::vector<GLfloat>* GetVertices();
		~Mesh();
		void InitBoundingBox();
		std::vector<glm::vec4>  UpdateBoundingBox(glm::mat4 transform);
		const std::vector<glm::vec4>* GetVertexBoundingBox();
	private:
		void PushVertex(GLfloat x, GLfloat y, GLfloat z);
		std::vector<GLfloat> vertex;
		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
		std::vector<glm::vec4> vertexBoundingBox;
	};
}


