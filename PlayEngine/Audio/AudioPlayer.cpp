#include "Audio/AudioPlayer.h"
#include <SDL.h>
#include <stdlib.h> 


AudioPlayer::AudioPlayer(const unsigned int handle, const std::string& name, const std::string& path) : Resource(handle, name, path)
{
    if (SDL_Init( SDL_INIT_AUDIO) < 0)
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


void AudioPlayer::PlaySoundEfect()
{
    if (shotSoundEfect == nullptr)
    {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    else 
    {
        Mix_PlayChannel(1, shotSoundEfect, 0);
    }
}

bool AudioPlayer::ReadFile()
{
    shotSoundEfect = Mix_LoadWAV(path.c_str());
    if (!shotSoundEfect)
    {
        printf("AudioPlayer (%s) failed to load: %s", path);
        return false;
    }
    return true;
}

Resource* AudioPlayer::Load()
{


    return this;
}

AudioPlayer:: ~AudioPlayer() 
{
    Mix_FreeChunk(shotSoundEfect);
}