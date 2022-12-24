#pragma once
#include "../Export.h"
#include <map>
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <GLFW\glfw3.h>
#include "Audio/AudioPlayer.h"

class PLAYENGINE Camera
{
public:
	Camera() = default;
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	virtual void keyControl(std::map<int, bool> keys, GLfloat deltaTime);
	virtual void mouseControl(GLfloat xChange, GLfloat yChange);

	virtual glm::mat4 calculateViewMatrix();
	virtual glm::vec3 getCameraPosition();
	virtual glm::vec3 getFront();
	~Camera();

protected:
	glm::vec3 position;
	glm::vec3 nextPosition;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;
	GLfloat prevXPos, prevYPos;
	float firstMove;

	void update();
};

