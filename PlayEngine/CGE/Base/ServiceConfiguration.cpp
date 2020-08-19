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

}

void ServiceConfiguration::getEntry(std::string entry, int& out)
{
	lua_getglobal(lState, entry.c_str());
	if (lua_isnumber(lState, -1))
	{
		out = (int)lua_tonumber(lState, -1);
	}
}
