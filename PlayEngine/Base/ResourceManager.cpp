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
#include <filesystem>

ResourceManager* ResourceManager::ptr = nullptr;
unsigned long ResourceManager::CounterImageUI = 0;
size_t ResourceManager::handleCount = 0;

ResourceManager* ResourceManager::GetPtr()
{
	if (ptr == nullptr)
	{
		ptr = new ResourceManager();
		//adidier llamar platform contiene la configuracion inicial del engine
		ptr->PathsReader("./Assets/");
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

Resource* ResourceManager::GetElement(const std::string& name)
{
	if (name.empty())
		return nullptr;

	for (auto i = resourceMap->begin(); i != resourceMap->end(); i++)
	{
		auto resource = i->second;
		if (resource != nullptr)
		{
			if (resource->GetName() == name)
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

void ResourceManager::PathsReader(std::string path, bool force)
{
	try {
		for (std::filesystem::directory_entry file : std::filesystem::directory_iterator(path))
		{
			const std::filesystem::path path = file.path();
			if (file.is_directory())
			{
				PathsReader(path.generic_string());
			}
			if (file.is_regular_file())
			{
				paths[path.filename().generic_string()] = path.generic_string();
			}
		}
	}
	catch(...)
	{
	}
}

std::string ResourceManager::GetPath(ResourceType type,const std::string &name)
{
	for (auto extensionType : ResourcesTypes[type])
	{
		auto path = paths.find(name + "." + extensionType);
		if (path != paths.end())
		{
			return path->second;
		}
	}
	return "";
}

unsigned int ResourceManager::Add(ResourceType type,const std::string& name)
{
	return AddResource(type, name, GetPath(type, name));
}

unsigned int ResourceManager::AddResource(ResourceType type, const std::string& name, const std::string& path)
{
	if (resourceMap == nullptr || name.empty() || path.empty())
		return -1;
	
	Resource* element = (Resource*)(GetElement(name));
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
		resource = new Graphic::Texture(1, name, path);//adidier quitar identificador / primer parametro
	}
	else if (type == ResourceType::ImageUI)
	{
		resource = new Graphic::ImageUI(CounterImageUI++, name, path);
	}
	else if (type == ResourceType::LineUI)
	{
		resource = new Graphic::LineUI(1);
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
	for (auto i = resourceMap->begin(); i != resourceMap->end(); ++i)
	{
		auto model = (i->second);
		model->Load();
	}
}


