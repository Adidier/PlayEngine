#pragma once
#include "../Export.h"
#include "Base/Resource.h"
#include <GL\glew.h>
#include <string>
//#include <SDL.h>
#include <SDL_mixer.h>

class PLAYENGINE MusicPlayer : public Resource
{
private:
	Mix_Music* backGround = nullptr;
	bool success = true;

public:

	MusicPlayer(const unsigned int handle, const std::string& name, const std::string& path = "./");
	virtual bool ReadFile() override;
	virtual Resource* Load() override;
	void PlayMusic();
	~MusicPlayer();
};