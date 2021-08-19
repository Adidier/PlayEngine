#include "Audio/MusicPlayer.h"
#include <SDL.h>
#include <stdlib.h> 
MusicPlayer::MusicPlayer(const unsigned int handle, const std::string& name, const std::string& path) : Resource(handle, name, path)
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
}

void MusicPlayer::PlayMusic()
{
    if (backGround == nullptr)
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    else
    {
        Mix_PlayMusic(backGround, 2);
    }
}

bool MusicPlayer::ReadFile()
{
    backGround = Mix_LoadMUS(path.c_str());
    if (!backGround)
    {
        printf("AudioPlayer (%s) failed to load: %s", path);
        return false;
    }
    return true;
}

Resource* MusicPlayer::Load()
{
    return this;
}

MusicPlayer:: ~MusicPlayer()
{
    Mix_FreeMusic(backGround);
}