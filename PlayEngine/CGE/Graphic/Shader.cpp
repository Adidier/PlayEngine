#include "Graphic/Shader.h"
namespace Graphics {
	Shader::Shader()
	{
		shaderID = 0;
	}

	void Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
	{
		CompileShader(vertexCode, fragmentCode);
	}

	void Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
	{
		std::string vertexString = ReadFile(vertexLocation);
		std::string fragmentString = ReadFile(fragmentLocation);
		const char* vertexCode = vertexString.c_str();
		const char* fragmentCode = fragmentString.c_str();

		CompileShader(vertexCode, fragmentCode);
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

	void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
	{
		shaderID = glCreateProgram();

		if (!shaderID)
		{
			printf("Error creating shader program!\n");
			return;
		}

		AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
		AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

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

		ids["projection"] = glGetUniformLocation(shaderID, "projection");
		ids["model"] = glGetUniformLocation(shaderID, "model");
		ids["view"] = glGetUniformLocation(shaderID, "view");
		ids["color1"] = glGetUniformLocation(shaderID, "color1");
		ids["color2"] = glGetUniformLocation(shaderID, "color2");
		ids["myLightPosition"] = glGetUniformLocation(shaderID, "myLightPosition");//quitar adidier
		ids["mainTex"] = glGetUniformLocation(shaderID, "mainTex");
		ids["rTex"] = glGetUniformLocation(shaderID, "rTex");
		ids["gTex"] = glGetUniformLocation(shaderID, "gTex");
		ids["bTex"] = glGetUniformLocation(shaderID, "bTex");
		ids["blendTexture"] = glGetUniformLocation(shaderID, "blendTexture");
		ids["normalMap"] = glGetUniformLocation(shaderID, "normalMap");

		/*Material*/
		uniformDirectionalLight.uniformColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
		uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
		uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
		uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
		ids["material.specularIntensity"] = glGetUniformLocation(shaderID, "material.specularIntensity");
		ids["material.shininess"] = glGetUniformLocation(shaderID, "material.shininess");
		ids["eyePosition"] = glGetUniformLocation(shaderID, "eyePosition");

		ids["pointLightCount"] = glGetUniformLocation(shaderID, "pointLightCount");

		for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
		{
			char locBuff[100] = { '\0' };

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.colour", i);
			uniformPointLight[i].uniformColour = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
			uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
			uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
			uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
			uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
			uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

			snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
			uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
		}
	}

	GLuint Shader::GetUniformId(const std::string& id)
	{
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

	void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
	{
		GLuint theShader = glCreateShader(shaderType);

		const GLchar* theCode[1];
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
	}

	Shader::~Shader()
	{
		ClearShader();
	}

	void Shader::SetDirectionalLight(Graphics::Lights::DirectionalLight* dLight)
	{
		dLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColour,
			uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
	}

	void Shader::SetPointLights(Graphics::Lights::PointLight* pLight, unsigned int lightCount)
	{
		if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

		glUniform1i(GetUniformId("pointLightCount"), lightCount);

		for (size_t i = 0; i < lightCount; i++)
		{
			pLight[i].UseLight(uniformPointLight[i].uniformAmbientIntensity, uniformPointLight[i].uniformColour,
				uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
				uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
		}
	}
	GLuint Shader::GetAmbientColourLocation()
	{
		return uniformDirectionalLight.uniformColour;
	}
	GLuint Shader::GetAmbientIntensityLocation()
	{
		return uniformDirectionalLight.uniformAmbientIntensity;
	}
	GLuint Shader::GetDiffuseIntensityLocation()
	{
		return uniformDirectionalLight.uniformDiffuseIntensity;
	}
	GLuint Shader::GetDirectionLocation()
	{
		return uniformDirectionalLight.uniformDirection;
	}
}
