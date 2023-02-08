#include "ScriptEnemy.h"
#include "lua.hpp"
#include <iostream>

ScriptEnemy::ScriptEnemy(const std::string &luaFile)
{
	L = luaL_newstate();
	luaL_openlibs(L);
	luaopen_base(L);
	luaopen_string(L);
	luaopen_math(L);

	if (luaL_loadfile(L, luaFile.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		std::cout<<"cannot run enemy file: %s"<< lua_tostring(L, -1);
	}
}

std::string ScriptEnemy::GetAction(double distance)
{
	lua_getglobal(L, "action");
	lua_pushnumber(L, distance);

	if (lua_pcall(L, 1, 1, 0) != 0)
		printf("error running function GetAction: %s", lua_tostring(L, -1));

	if (!lua_isstring(L, -1))
		printf("function `GetAction must return a string");

	std::string action = lua_tostring(L, -1);
	lua_pop(L, 1);
	return action;
}
