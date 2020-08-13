#pragma once
#include "../Export.h"
#include <GL\glew.h>
#include <vector>
#include "glm.hpp"
namespace Physics {
	class PLAYENGINE Physics
	{
	private:
		static glm::vec3 GetMin(std::vector<glm::vec4> vector)
		{
			GLfloat minX = vector[0].x;
			GLfloat minY = vector[0].y;
			GLfloat minZ = vector[0].z;
			for (auto element : vector)
			{
				if (element.x < minX)
				{
					minX = element.x;
				}
				if (element.y < minY)
				{
					minY = element.y;
				}
				if (element.z < minZ)
				{
					minZ = element.z;
				}
			}
			return glm::vec3(minX, minY, minZ);
		}


		static glm::vec3 GetMax(std::vector<glm::vec4> vector)
		{
			GLfloat maxX = vector[0].x;
			GLfloat maxY = vector[0].y;
			GLfloat maxZ = vector[0].z;
			for (auto element : vector)
			{
				if (element.x > maxX)
				{
					maxX = element.x;
				}
				if (element.y > maxY)
				{
					maxY = element.y;
				}
				if (element.z > maxZ)
				{
					maxZ = element.z;
				}
			}
			return glm::vec3(maxX, maxY, maxZ);
		}

	public:

		static bool CheckColision(std::vector<glm::vec4> box1, std::vector<glm::vec4> box2)
		{
			auto amin = GetMin(box1);
			auto bmin = GetMin(box2);

			auto amax = GetMax(box1);
			auto bmax = GetMax(box2);

			return	(amin.x <= bmax.x && amax.x >= bmin.x) &&
				(amin.y <= bmax.y && amax.y >= bmin.y) &&
				(amin.z <= bmax.z && amax.z >= bmin.z);

		}
	};
}

