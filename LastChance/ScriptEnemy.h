#pragma once
#include <string>

class ScriptEnemy
{
public:
	ScriptEnemy(std::string luaFile);
	float Rotate(float Forwardx, float Forwardy, float Forwardz,float x, float y, float z);
};

