/**************************************************************************************************************
* Audio Manager - Code
*
* The code file for the Audio manager class. Initiates the audio mixer, creates each sound from the array of audio file paths
* and adds them to an array of sounds. 
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/

#include "AudioManager.h"

AudioManager::AudioManager()
{
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) == -1)
    {
        std::cout << "couldn't start audio \n";
        return;
    }

    for (const auto& soundPath : soundPaths)
    {
        std::stringstream file;
        file << soundPath;
        Mix_Chunk* newSound = Mix_LoadWAV(file.str().c_str());
        sounds.push_back(newSound);
    }

    Mix_Volume(0, 20);
    Mix_Volume(1, 50);
    Mix_Volume(2, 50);
}

void AudioManager::PlaySound(Esounds sound) const
{
    // Stop the other sounds first if not allowed to overlap
    short index;
    switch (sound)
    {
        case Esounds::Gunshot:
            index = 0;
            break;
        
        case Esounds::Reload:
            index = 1;
            break;

        case Esounds::Empty:
            index = 2;
            break;

    }

    // Giving them their own channel so that the sounds overlap properly
    Mix_PlayChannel(index, sounds[index], 0);
}
