#include "Graphic/Mesh.h"
#include "glm.hpp"
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
#include "Base/ShaderManager.h"
namespace Graphics {
	Mesh::Mesh()
	{
		VAO = 0;
		VBO = 0;
		IBO = 0;
		indexCount = 0;
	}

	void Mesh::CreateMesh(std::vector<GLfloat> vNTU, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices, unsigned int vSize)
	{
		indexCount = numOfIndices;

		for (int i = 0; i < vNTU.size(); i += vSize)
		{
			GLfloat x = vNTU[i];
			GLfloat y = vNTU[i + 1];
			GLfloat z = vNTU[i + 2];
			this->vertex.push_back(x);
			this->vertex.push_back(y);
			this->vertex.push_back(z);
		}

		InitBoundingBox();

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVertices, &vNTU[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, 0);
		glEnableVertexAttribArray(0);
		if (vSize > 3) {
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 3));
			glEnableVertexAttribArray(1);
		}
		if (vSize > 5) {
			glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 5));
			glEnableVertexAttribArray(2);
		}
		if (vSize > 8) {
			glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * vSize, (void*)(sizeof(GLfloat) * 8));
			glEnableVertexAttribArray(3);
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void Mesh::RenderMesh()
	{
		glBindVertexArray(VAO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	const std::vector<GLfloat>* Mesh::GetVertices()
	{
		return &vertex;
	}
	void Mesh::ClearMesh()
	{
		if (IBO != 0)
		{
			glDeleteBuffers(1, &IBO);
			IBO = 0;
		}

		if (VBO != 0)
		{
			glDeleteBuffers(1, &VBO);
			VBO = 0;
		}

		if (VAO != 0)
		{
			glDeleteVertexArrays(1, &VAO);
			VAO = 0;
		}

		indexCount = 0;
	}


	Mesh::~Mesh()
	{
		ClearMesh();
	}

	void Mesh::PushVertex(GLfloat x, GLfloat y, GLfloat z)
	{
		vertexBoundingBox.push_back(glm::vec4(x, y, z, 1));
	}

	void Mesh::InitBoundingBox()
	{
		std::vector<GLfloat> min(3);
		std::vector<GLfloat> max(3);
		min[0] = max[0] = vertex[0];
		min[1] = max[1] = vertex[1];
		min[2] = max[2] = vertex[2];
		for (int i = 0; i < vertex.size(); i += 3)
		{
			if (vertex[i] < min[0]) min[0] = vertex[i];
			if (vertex[i] > max[0]) max[0] = vertex[i];
			if (vertex[i + 1] < min[1]) min[1] = vertex[i + 1];
			if (vertex[i + 1] > max[1]) max[1] = vertex[i + 1];
			if (vertex[i + 2] < min[2]) min[2] = vertex[i + 2];
			if (vertex[i + 2] > max[2]) max[2] = vertex[i + 2];
		}
		PushVertex(min[0], min[1], min[2]);
		PushVertex(max[0], min[1], min[2]);
		PushVertex(max[0], min[1], max[2]);
		PushVertex(min[0], min[1], max[2]);
		PushVertex(min[0], max[1], min[2]);
		PushVertex(max[0], max[1], min[2]);
		PushVertex(max[0], max[1], max[2]);
		PushVertex(min[0], max[1], max[2]);
	}

	const std::vector<glm::vec4>* Mesh::GetVertexBoundingBox()
	{
		return &vertexBoundingBox;
	}

	std::vector<glm::vec4>  Mesh::UpdateBoundingBox(glm::mat4 transform)
	{
		std::vector<glm::vec4> vector;
		for (auto element : vertexBoundingBox)
		{
			vector.push_back(transform * element);
		}
		return vector;
	}
}