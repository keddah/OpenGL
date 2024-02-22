/**************************************************************************************************************
* Audio Manager - Header
*
* The header file for the Audio manager class. Responsible for providing the file paths for each audio file that it can play.
* Also declares an enum of the different sounds
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#pragma once

#include <iostream>
#include <SDL_mixer.h>
#include <sstream>
#include <vector>

class AudioManager
{
public:
    AudioManager();
    ~AudioManager()
    {
        for(const auto& sfx : sounds) Mix_FreeChunk(sfx);
        Mix_FreeMusic(soundPlayer);
    }

    enum class Esounds
    {
        Gunshot,
        Reload,
        Empty
    };
    
    // Overlap = can play over other sounds
    void PlaySound(Esounds sound) const;

private:
    Mix_Music* soundPlayer;
    std::vector<Mix_Chunk*> sounds;

    static constexpr short soundsLength = 3;
    
    // The order of the array affects the selection of the sound
    const std::string soundPaths[soundsLength]
    {
        "Audio/gunshot.wav",
        "Audio/reload.wav",
        "Audio/empty.wav"
    };

    const short sfxChannel = 1;
};
