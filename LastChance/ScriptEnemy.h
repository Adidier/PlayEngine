#pragma once
#include <string>
#include "lua.hpp"

class ScriptEnemy
{
private:
	lua_State* L = nullptr;
public:
	ScriptEnemy(const std::string &luaFile);
	std::string GetAction(double distance);

};

