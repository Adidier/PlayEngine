#pragma once
#include "../Export.h"
#include <string>
#include "GameState.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Base/ServiceConfiguration.h"
#include<map>

class GameState;
class PLAYENGINE Platform
{
private:
	int width;
	int height;
	std::string name;
	GLFWwindow* mainWindow;
	GLint bufferWidth, bufferHeight;
	float deltaTime{ 0 };
	float lastTime{ 0 };
	ServiceConfiguration *serviceConfiguration;
private:
	void Init();
	Platform(std::string name);
	~Platform();
	static Platform* ptr;
public:
	static Platform* GetPtr();
	void RenderClear();
	void RenderPresent();
	void CheckEvent(GameState* obj, bool (GameState::* keyboard)(std::map<int, bool>), bool (GameState::* mouse)(int, int, bool));
	int GetWidth();
	int GetHeight();
	float GetDeltaTime();
	bool shouldWindowClose();
	static int mouseX;
	static int mouseY;
public:
	static GameState* obj;
	static bool (GameState::* keyboard)(std::map<int, bool>);
	static bool (GameState::* mouse)(int, int, bool);
	static std::map<int, bool> keys;
	static bool leftButtonMouse;
private:
	static void HandleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void HandleMousePosition(GLFWwindow* window, double x, double y);
	static void HandleMouseButton(GLFWwindow* window, int button, int action, int mod);
};