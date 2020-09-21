#pragma once

#include "../Export.h"
#include "Base/Resource.h"
#include <GL\glew.h>
#include <string>
//#include <SDL.h>
#include <SDL_mixer.h>

class PLAYENGINE AudioPlayer : public Resource
{
private:
	Mix_Chunk* shotSoundEfect = nullptr;
	std::string pathToFile;
	bool success = true;

public:

	AudioPlayer(const unsigned int handle, const std::string& name, const std::string& path = "./");
	virtual bool ReadFile() override;
	virtual Resource* Load() override;
	void PlaySoundEfect();
	~AudioPlayer();
};