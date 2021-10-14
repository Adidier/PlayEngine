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
	void UseShader();
	void ClearShader();
	////Material
	GLuint GetAmbientIntensityLocation();
	GLuint GetAmbientColourLocation();
	GLuint GetDiffuseIntensityLocation();
	GLuint GetDirectionLocation();
	~Shader();
	void SetDirectionalLight(DirectionalLight* dLight);
	void SetPointLights(PointLight* pLight, unsigned int lightCount);
	void SetUniform(std::string variable, glm::mat4 matrix);
	void SetUniform(std::string variable, glm::vec3 vector);

	GLuint GetUniformId(const std::string& id);//adidier moverla a privada en futuro 
private:
	GLuint shaderID;
	std::map<std::string, GLuint> ids;
	void Compile(const char* vertexCode, const char* fragmentCode);
	void Add(GLuint theProgram, const char* shaderCode, GLenum shaderType);	
};

