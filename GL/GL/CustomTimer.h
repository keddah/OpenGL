/**************************************************************************************************************
* Custom Timer - Header
*
* A static class that's used to produce a delta time which can be used to make timers.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/


#pragma once

#include <chrono>
#include <SDL_timer.h>

class Time 
{
public:
    static void Update() 
    {
        deltaTime = newTime - currentTime;
        currentTime = newTime;
    }

    static void SetLastFrameTime()
    {
        SetElapsedTime();
        newTime = elapsedGameTime;
    }

    static float GetElapsedTime() { return elapsedGameTime; }
    static void SetElapsedTime()
    {
        elapsedGameTime = SDL_GetTicks();
        elapsedGameTime *= .001f;
    }
    static float GetDeltaTime() { return deltaTime; }
    
    static void SetCurrentTime(float time) { currentTime = time; }

private:
    static float elapsedGameTime;
    static float currentTime;
    static float newTime;
    static float deltaTime;
};