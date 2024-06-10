#pragma once
#include <vector>
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>

class Sound {
public:
    std::vector<Mix_Chunk*> sounds;
    std::vector<Mix_Music*> music;
    int volume;


    int loadMusic(const char* filename);
    int loadSound(const char* filename);

    void setVolume(int v);

    int playMusic(int m);
    int playSound(int s);

    int initMixer();
    void quitMixer();

    void togglePlay();
};