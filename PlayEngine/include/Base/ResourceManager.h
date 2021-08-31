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

const std::vector<std::vector<std::string>> ResourcesTypes = { {"obj","fbx"},{"png","jpg"},{"png"},{"png"},{"wav"} ,{"wav"} };

/*
cargar todos los archivos de capeta Assets en memoria
configuracion se va a asignar el directorio a cargar si no esta definido sera Assets

map<nombre,path> assets;
addAsset agrega archivos al mapa
getPath obtiene los paths de los assets

*/

class PLAYENGINE ResourceManager
{
	public:
		std::mutex mu;
	private:
		static size_t handleCount;
		std::list<std::thread*> pool;
		std::map<size_t, Resource*>* resourceMap;
		std::map<std::string, std::string> paths;
		ResourceManager();
		~ResourceManager();
		static ResourceManager* ptr;
		unsigned int AddResource(ResourceType type, const std::string& name, const  std::string& path);
		void PathsReader(std::string path, bool force = false);
		std::string GetPath(ResourceType type,const std::string &name);
	public:

		static ResourceManager* GetPtr();
		void ClearResources();
		void GetSafeOpenIds(unsigned int& a);
		size_t GetSize();
		const Resource* GetElement(const std::string& name);
		void Wait();
		void Load();
		unsigned int Add(ResourceType type,const std::string& name);
};