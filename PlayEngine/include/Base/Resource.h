#pragma once
#include "../Export.h"
#include <string>

class PLAYENGINE Resource
{
protected:
	std::string	name;
	std::string	path;
	std::string	filename;
	unsigned int handle;
public:
	Resource(const unsigned int handle, const std::string& name, const std::string& path = "./");

	std::string GetName();

	std::string GetPath();

	std::string GetFilename();

	unsigned int GetHandle();

	virtual bool ReadFile() = 0;
	virtual Resource* Load() =0;
};
