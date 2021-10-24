#pragma once
#include "../Export.h"
#include "Graphic/Model.h"
#include "Audio/AudioPlayer.h"
#include "Audio/MusicPlayer.h"
#include <map>
#include <thread> 
#include <list> 
#include <mutex>

enum ResourceType
{
	Model3d,
	Texture,
	ImageUI,
	LineUI,
	Sound,
	Music,
	VertexShader,
	FragmentShader,
	Configuration,
};

const std::vector<std::vector<std::string>> ResourcesTypes = { {"obj","fbx"},{"png","jpg"},{"png"},{"png"},{"wav"} ,{"wav"} ,{"vert"}, {"frag"} ,{"lua"} };


class PLAYENGINE ResourceManager
{
	private:
		std::mutex mu;
		static size_t handleCount;
		static unsigned long CounterImageUI;
		std::list<std::thread*> pool;
		std::map<size_t, Resource*>* resourceMap;
		std::map<std::string, std::string> paths;
		ResourceManager();
		~ResourceManager();
		static ResourceManager* ptr;
		unsigned int AddResource(ResourceType type, const std::string& name, const  std::string& path);
		void PathsReader(std::string path, bool force = false);
	public:
		std::string GetPath(ResourceType type, const std::string& name);
		static ResourceManager* GetPtr(const std::string& path = "");
		void ClearResources();
		void GetSafeOpenIds(unsigned int& a);
		size_t GetSize();
		Resource* GetElement(const std::string& name);
		void Wait();
		void Load();
		unsigned int Add(ResourceType type,const std::string& name);
};