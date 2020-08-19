#pragma once
#include <string>
#include "Lua.hpp"

class ServiceConfiguration
{
private:
	ServiceConfiguration(){};
	~ServiceConfiguration(){};
	lua_State* lState = nullptr;
	static ServiceConfiguration* sc;
public:
	static ServiceConfiguration* getptr();
	void load(std::string s);

	void getEntry(std::string entry, int &out);

};

