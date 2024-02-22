/**************************************************************************************************************
* Controllers - Header
*
* The header file for the Player controller class. Responsible for providing get functions for the player class so that
* it can read inputs (everything is private). 
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#pragma once

#include <vec2.hpp>
#include <iostream>
#include "SDL.h"

#define print(x) { std::cout << x << std::endl; }

class Controller
{
public:
    Controller() = default;
    Controller(bool& running);
    ~Controller() = default;

    void Update() { ClearMouseDelta(); CheckInputs(); }
    
    glm::vec2 GetMouseDelta() const { return mouseDelta; }
    void ClearMouseDelta() { mouseDelta = glm::vec2(); }
    
    bool* GetMoveInputs() { return moveInputs; }
    bool JumpBtnDown() const { return jump; }
    bool ShiftBtnDown() const { return sprint; }
    bool CrouchBtnDown() const { return crouch; }
    
    bool LmbDown() const { return lmb; }
    bool RmbDown() const { return rmb; }
    
    bool RKeyDown() const { return reload; }
    
private:
    void CheckInputs();

    bool& rRunning;

    int screenWidth, screenHeight;
    
    bool moveInputs[4];
    glm::vec2 mousePos;
    glm::vec2 mouseDelta;

    bool lmb, rmb;

    bool sprint, jump, crouch, reload;
};
