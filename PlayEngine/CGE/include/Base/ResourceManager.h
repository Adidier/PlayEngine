#pragma once
#include "../Export.h"
#include "Resource.h"
#include <map>

enum ResourceType
{
	Model3d,
	Texture,
	Sound
};

class PLAYENGINE ResourceManager
{
private:
	static size_t handleCount;
	std::map<size_t, Resource*>* resourceMap;
	ResourceManager();
	~ResourceManager();
	static ResourceManager* ptr;

public:



	static ResourceManager* GetPtr();
	void ClearResources();

	size_t GetSize();
	Resource* GetElement(const std::string& name, const std::string& path);
	//Resource* GetElement(const std::string& name, const std::string& path = "./");
	/*
	Resource* GetElement(const int handle)
	void Remove(const unsigned int handle)
	*/
	unsigned int Add(ResourceType type, const std::string& name, const std::string& path = "./");
};