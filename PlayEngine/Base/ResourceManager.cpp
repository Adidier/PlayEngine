#pragma once
#include "Base/ResourceManager.h"
#include "Base/Resource.h"
#include "Graphic/Model.h"
#include "Graphic/Texture.h"
#include "Graphic/GUI_IMAGE.h"
#include "Graphic/GUILine.h"
#include "Audio/AudioPlayer.h"
#include "Audio/MusicPlayer.h"

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

void ResourceManager::GetSafeOpenIds(unsigned int& a)
{
	//mu.lock();
	GLuint VAO;
	glGenBuffers(1, &VAO);
	GLenum loop_error = glGetError();
	a = VAO;
	//mu.unlock();
}
void ResourceManager::ClearResources()
{
	for (auto resource = resourceMap->begin(); resource != resourceMap->end(); ++resource)
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

void ResourceManager::Wait()
{
	for (auto& th : pool)
	{
		if (th->joinable())
		{
			th->join();
		}
	}
}
unsigned int ResourceManager::Add(ResourceType type,const std::string& name,const std::string& path)
{
	AddResource(type, name, path);
	return -1;//adidier arreglado
}

unsigned int ResourceManager::AddResource(ResourceType type, const std::string& name, const std::string& path)
{
	if (resourceMap == nullptr || name.empty() || path.empty())
		return -1;
	
	Resource* element = GetElement(name, path);
	if (element != nullptr)
	{
		return element->GetHandle();
	}
	
	Resource* resource = nullptr;
	handleCount++;
	//TODO mejorar
	if (type == ResourceType::Model3d)
	{
		resource = new Graphic::Model(name,path);
	}
	else if (type == ResourceType::Texture)
	{
		resource = new Graphic::Texture(1, name, path);
	}
	else if (type == ResourceType::GUI_Image)
	{
		resource = new Graphic::GuiImage(1, name, path);
	}
	else if (type == ResourceType::GUILine)
	{
		resource = new Graphic::GUILine(1);
	}
	else if (type == ResourceType::Sound)
	{
		resource = new AudioPlayer(2, name, path);
	}
	else if (type == ResourceType::Music)
	{
		resource = new MusicPlayer (3, name, path);
	}

	std::thread* thr = new std::thread(&Resource::ReadFile, resource);
	pool.push_back(thr);
	resourceMap->insert(std::make_pair(handleCount, resource));
}

void ResourceManager::Load()
{
	for (auto i = resourceMap->begin(); i != resourceMap->end(); i++)
	{
		auto model = (i->second);
		model->Load();
	}
}


