#include "ScriptEnemy.h"
#include "lua.hpp"
ScriptEnemy::ScriptEnemy(std::string luaFile) {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luaopen_base(L);
	luaopen_string(L);
	luaopen_math(L);

	if (luaL_loadfile(L, luaFile.c_str()) || lua_pcall(L, 0, 0, 0))
	{
		printf("cannot run configuration file: %s", lua_tostring(L, -1));
	}

}
