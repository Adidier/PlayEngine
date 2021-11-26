#include "Graphic/Shader.h"
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

Shader::Shader()
{
	shaderID = 0;
}

void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
	Compile(vertexCode, fragmentCode);
}

void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
	std::string vertexString = ReadFile(vertexLocation);
	std::string fragmentString = ReadFile(fragmentLocation);
	if (!vertexString.empty() && !fragmentString.empty())
	{
		Compile(vertexString.c_str(), fragmentString.c_str());
	}
}

std::string Shader::ReadFile(const char* fileLocation)
{
	std::string content;
	std::ifstream fileStream(fileLocation, std::ios::in);

	if (!fileStream.is_open()) {
		printf("Failed to read %s! File doesn't exist.", fileLocation);
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

void Shader::Compile(const char* vertexCode, const char* fragmentCode)
{
	shaderID = glCreateProgram();

	if (!shaderID)
	{
		printf("Error creating shader program!\n");
		return;
	}

	Add(shaderID, vertexCode, GL_VERTEX_SHADER);
	Add(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glLinkProgram(shaderID);
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error linking program: '%s'\n", eLog);
		return;
	}

	glValidateProgram(shaderID);
	glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
		printf("Error validating program: '%s'\n", eLog);
		return;
	}
}

GLuint Shader::GetUniformId(const std::string &id)
{
	if (ids.find(id) != ids.end())
	{
		ids[id] = glGetUniformLocation(shaderID, id.c_str());
	}

	return ids[id];
}

void Shader::UseShader()
{
	glUseProgram(shaderID);
}

void Shader::ClearShader()
{
	if (shaderID != 0)
	{
		glDeleteProgram(shaderID);
		shaderID = 0;
	}
}

void Shader::Add(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
	GLuint theShader = glCreateShader(shaderType);

	const GLchar* theCode[1];//Adidier regresar mejorar el manejo de este apuntador en  glShaderSource
	theCode[0] = shaderCode;

	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);

	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };

	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
		printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
		return;
	}

	glAttachShader(theProgram, theShader);
	glDeleteShader(theShader);
}

Shader::~Shader()
{
	ClearShader();
}

void Shader::SetUniform(std::string variable, glm::mat4 matrix)
{
	int id = GetUniformId(variable);
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetUniform(std::string variable, glm::vec3 vector)
{
	int id = GetUniformId(variable);
	glUniform3f(id, vector.x, vector.y, vector.z);
}

void Shader::SetUniform(std::string variable, int value)
{
	int id = GetUniformId(variable);
	glUniform1i(id, value);
}

void Shader::SetUniform(std::string variable, float value)
{
	int id = GetUniformId(variable);
	glUniform1f(id, value);
}
