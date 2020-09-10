#pragma once

#include "../Export.h"
#include "Base/Resource.h"
#include <GL\glew.h>
#include <string>
#include <SDL.h>
#include <SDL_mixer.h>
class PLAYENGINE AudioPlayer
{
private:
	Mix_Music* backGround = nullptr;
	bool success = true;

public:

	AudioPlayer(/*const std::string& audioname, const std::string& path = "./"*/);
	void PlayMusic();
	~AudioPlayer();
};