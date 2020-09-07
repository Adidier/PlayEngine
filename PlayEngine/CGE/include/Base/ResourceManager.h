#pragma once
#include "../Export.h"
#include "Graphic/Model.h"
#include <map>
#include <thread> 
#include <list> 
#include <mutex>

enum ResourceType
{
	Model3d,
	Texture,
	Sound
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
		unsigned int AddElementToPool(ResourceType type, const std::string& name, const  std::string& path);
		void Load();
		unsigned int Add(ResourceType type,const std::string& name, const std::string& path = "./");
};