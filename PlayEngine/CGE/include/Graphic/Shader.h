#pragma once
#include "../Export.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <GL\glew.h>
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"

namespace Graphics 
{
	const int MAX_POINT_LIGHTS = 3;

	class PLAYENGINE Shader
	{
	private:

		struct {
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformPosition;
			GLuint uniformConstant;
			GLuint uniformLinear;
			GLuint uniformExponent;
		} uniformPointLight[MAX_POINT_LIGHTS];
		struct {
			GLuint uniformColour;
			GLuint uniformAmbientIntensity;
			GLuint uniformDiffuseIntensity;

			GLuint uniformDirection;
		} uniformDirectionalLight;
	public:
		Shader();
		void CreateFromString(const char* vertexCode, const char* fragmentCode);
		void CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);
		std::string ReadFile(const char* fileLocation);
		GLuint GetUniformId(const std::string& id);
		void UseShader();
		void ClearShader();
		////Material
		GLuint GetAmbientIntensityLocation();
		GLuint GetAmbientColourLocation();
		GLuint GetDiffuseIntensityLocation();
		GLuint GetDirectionLocation();
		~Shader();
		void SetDirectionalLight(Graphics::Lights::DirectionalLight* dLight);
		void SetPointLights(Graphics::Lights::PointLight* pLight, unsigned int lightCount);
	private:
		GLuint shaderID;
		std::map<std::string, GLuint> ids;
		void CompileShader(const char* vertexCode, const char* fragmentCode);
		void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
	};
}

