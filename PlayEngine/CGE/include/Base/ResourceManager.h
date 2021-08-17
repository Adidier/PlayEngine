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
	GUI_Image,
	GUILine,
	Sound,
	Music
};

class PLAYENGINE ResourceManager
{
	public:
		std::mutex mu;
	private:
		static size_t handleCount;
		std::list<std::thread*> pool;
		std::map<size_t, Resource*>* resourceMap;
		ResourceManager();
		~ResourceManager();
		static ResourceManager* ptr;

	public:

		static ResourceManager* GetPtr();
		void ClearResources();
		void GetSafeOpenIds(unsigned int& a);
			size_t GetSize();
		Resource* GetElement(const std::string& name, const std::string& path);

		void Wait();
		unsigned int AddResource(ResourceType type, const std::string& name, const  std::string& path);
		void Load();
		unsigned int Add(ResourceType type,const std::string& name, const std::string& path = "./");
};