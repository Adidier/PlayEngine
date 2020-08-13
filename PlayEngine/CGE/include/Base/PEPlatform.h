#pragma once
#include "../Export.h"
#include <string>
#include "GameState.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include<map>
namespace Base {
	class GameState;
	class PLAYENGINE PEPlatform
	{
	private:
		int width;
		int height;
		std::string name;
		GLFWwindow* mainWindow;
		GLint bufferWidth, bufferHeight;
		float deltaTime{ 0 };
		float lastTime{ 0 };
	private:
		void init();
		PEPlatform(std::string name, int wWindow, int hWindow);
		~PEPlatform();
		static PEPlatform* ptr;
	public:
		static PEPlatform* GetPtr();

		void RenderClear();
		void RenderPresent();
		void CheckEvent(GameState* obj, bool (GameState::* keyboard)(std::map<int, bool>), bool (GameState::* mouse)(int, int, bool));
		int GetWidth();
		int GetHeight();
		float GetDeltaTime();
		bool shouldWindowClose();
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
}