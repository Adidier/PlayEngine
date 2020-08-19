#pragma once
#include "Base/ResourceManager.h"
#include "Base/Resource.h"
#include "Graphic/Model.h"
#include <map>

ResourceManager* ResourceManager::ptr = nullptr;
size_t ResourceManager::handleCount = 0;

ResourceManager* ResourceManager::GetPtr()
{
	if (ptr == nullptr)
	{
		ptr = new ResourceManager();
	}
	return ptr;
}

ResourceManager::ResourceManager()
{
	resourceMap = new std::map<size_t, Resource*>;
}

ResourceManager::~ResourceManager()
{
	ClearResources();
	delete resourceMap;
}

void ResourceManager::ClearResources()
{
	for (auto resource = resourceMap->begin(); resource != resourceMap->end(); resource++)
	{
		delete resource->second;
	}
	resourceMap->clear();
}

size_t ResourceManager::GetSize()
{
	_ASSERT(resourceMap, "log");
	return resourceMap->size();//adidier revisar validaciones
}

Resource* ResourceManager::GetElement(const std::string& name, const std::string& path)
{
	if (name.empty() || path.empty())
		return nullptr;

	for (auto i = resourceMap->begin(); i != resourceMap->end(); i++)
	{
		auto resource = i->second;
		if (resource != nullptr)
		{
			if (resource->GetName() == name && resource->GetPath() == path)
			{
				return resource;
			}
		}
	}

	return nullptr;
}

unsigned int ResourceManager::Add(ResourceType type, const std::string& name, const std::string& path)
{
	if (resourceMap == nullptr || name.empty() || path.empty())
		return -1;//adidier
	
	Resource* element = GetElement(name, path);
	if (element != nullptr)
	{
		return element->GetHandle();
	}

	Resource* resource = nullptr;
	handleCount++;
	if (type == ResourceType::Model3d)
	{
		resource = new Model(name,path);
	}
	resource->Load();
	resourceMap->insert(std::make_pair(handleCount, resource));
	return handleCount;
}


