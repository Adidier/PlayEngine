#include "Base/PEPlatform.h"
#include <iostream>
namespace Base {
	PEPlatform* PEPlatform::ptr;
	GameState* PEPlatform::obj;

	bool (GameState::* PEPlatform::keyboard)(std::map<int, bool>);
	bool (GameState::* PEPlatform::mouse)(int, int, bool);
	std::map<int, bool> PEPlatform::keys;
	bool PEPlatform::leftButtonMouse;

	PEPlatform::PEPlatform(std::string name, int wWindow, int hWindow)
	{
		width = wWindow;
		height = hWindow;
		this->name = name;
		init();
		for (size_t i = 0; i < 1024; i++)
		{
			keys[i] = 0;
		}
	}

	void PEPlatform::init()
	{
		if (!glfwInit())
		{
			std::cout << "Error Initialising GLFW";
			glfwTerminate();
			return;
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

		mainWindow = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
		if (!mainWindow)
		{
			printf("Error creating GLFW window!");
			glfwTerminate();
			return;
		}

		// Get buffer size information
		glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

		// Set the current context
		glfwMakeContextCurrent(mainWindow);
		glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		// Allow modern extension access
		glewExperimental = GL_TRUE;

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			printf("Error: %s", glewGetErrorString(error));
			glfwDestroyWindow(mainWindow);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEPTH_TEST);

		// Create Viewport
		glViewport(0, 0, bufferWidth, bufferHeight);
	}
	PEPlatform::~PEPlatform()
	{
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
	}

	void PEPlatform::RenderClear()
	{
		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void PEPlatform::RenderPresent()
	{
		glfwSwapBuffers(mainWindow);
	}

	float PEPlatform::GetDeltaTime()
	{
		return deltaTime;
	}

	void PEPlatform::CheckEvent(GameState* obj, bool (GameState::* keyboard)(std::map<int, bool>), bool (GameState::* mouse)(int, int, bool))
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;
		glfwPollEvents();
		this->obj = obj;
		this->keyboard = keyboard;
		this->mouse = mouse;
		glfwSetKeyCallback(mainWindow, HandleKeys);
		glfwSetCursorPosCallback(mainWindow, HandleMousePosition);
		glfwSetMouseButtonCallback(mainWindow, HandleMouseButton);
	}
	int PEPlatform::GetWidth()
	{
		return width;
	}

	int PEPlatform::GetHeight()
	{
		return height;
	}

	PEPlatform* PEPlatform::GetPtr()
	{
		if (ptr == nullptr)
		{
			ptr = new PEPlatform("THE GAME", 800, 600);
		}
		return ptr;
	}

	void  PEPlatform::HandleKeys(GLFWwindow* window, int key, int code, int action, int mode)
	{
		if (key >= 0 && key < 1024)
		{
			if (action == GLFW_PRESS)
			{
				PEPlatform::keys[key] = true;
			}
			else if (action == GLFW_RELEASE)
			{
				PEPlatform::keys[key] = false;
			}
		}
		if (keys[GLFW_KEY_ESCAPE])
			glfwSetWindowShouldClose(window, 1);
		(PEPlatform::obj->*PEPlatform::keyboard)(keys);
	}


	void PEPlatform::HandleMousePosition(GLFWwindow* window, double x, double y)
	{
		(PEPlatform::obj->*PEPlatform::mouse)(x, y, leftButtonMouse);
	}

	void PEPlatform::HandleMouseButton(GLFWwindow* window, int button, int action, int mod)
	{
		(PEPlatform::obj->*PEPlatform::mouse)(-1, -1, action);

	}

	bool PEPlatform::shouldWindowClose() {
		return glfwWindowShouldClose(mainWindow);
	}
}