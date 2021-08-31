#include"Base/Resource.h"

Resource::Resource(const unsigned int handle, const std::string& name, const std::string& path)
{
	if (!name.empty())
		this->name = name;

	if (!path.empty())
		this->path = path;

	this->handle = handle;

	if (!name.empty() && !path.empty())
		this->filename = path + name;
}

std::string Resource::GetName()
{
	return name;
}

std::string Resource::GetPath()
{
	return path;
}

std::string Resource::GetFilename()
{
	return filename;
}

unsigned int Resource::GetHandle()
{
	return handle;
}


