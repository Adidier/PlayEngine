#include "Base/ServiceConfiguration.h"
#include <iostream>

ServiceConfiguration* ServiceConfiguration::sc = nullptr;

ServiceConfiguration* ServiceConfiguration::getptr() 
{
	if(sc == nullptr)
	{
		sc = new ServiceConfiguration();
	}
	return sc; 
};

double f(lua_State* l, double x, double y) {
	double z;

	lua_getglobal(l, "f");
	lua_pushnumber(l, x);
	lua_pushnumber(l, y);

	if (lua_pcall(l, 2, 1, 0) != 0)
		printf("error running function `f': %s", lua_tostring(l, -1));

	if (!lua_isnumber(l, -1))
		printf("function `f' must return a number");
	z = lua_tonumber(l, -1);
	lua_pop(l, 1);
	return z;
}

void ServiceConfiguration::load(std::string file)
{
	lState = luaL_newstate();
	luaL_openlibs(lState);
	luaopen_base(lState);
	if (luaL_loadfile(lState, file.c_str()) || lua_pcall(lState, 0, 0, 0))
	{
		printf("No se pudo abrir el archivo de configuracion: %s", lua_tostring(lState, -1));
		return;
	}
	
	double c = f(lState, 3.14, 2);
	/*
	lua_getglobal(lState, "width");
	lua_getglobal(lState, "height");
	if (!lua_isnumber(lState, -2))
	{
		printf("width should be a number\n");
	}
	if (!lua_isnumber(lState, -1))
	{
		printf("height should be a number\n");
	}
	int width = (int)lua_tonumber(lState, -2);
	int height = (int)lua_tonumber(lState, -1);
	lua_close(lState);*/

}

void ServiceConfiguration::getEntry(std::string entry, std::string& out)
{
	lua_getglobal(lState, entry.c_str());
	size_t size = 100;
	if (lua_tolstring(lState, -1, &size))
	{
		out = lua_tolstring(lState, -1, &size);
	}
}

void ServiceConfiguration::getEntry(std::string entry, bool& out)
{
	lua_getglobal(lState, entry.c_str());
	if (lua_toboolean(lState, -1))
	{
		out = (bool)lua_toboolean(lState, -1);
	}
}

void ServiceConfiguration::getEntry(std::string entry, int& out)
{
	lua_getglobal(lState, entry.c_str());
	if (lua_isnumber(lState, -1))
	{
		out = (int)lua_tonumber(lState, -1);
	}
}
