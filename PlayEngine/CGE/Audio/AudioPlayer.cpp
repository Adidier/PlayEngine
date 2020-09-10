#include "Audio/AudioPlayer.h"

AudioPlayer::AudioPlayer(/*const std::string& audioname, const std::string& path = "./"*/)
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

void AudioPlayer::PlayMusic()
{
    /*backGround = Mix_LoadMUS("PlayEngine/LastChance/Assets/Sounds/beat.wav");
    if (backGround == nullptr) 
    {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }*/
}

AudioPlayer:: ~AudioPlayer() 
{

}