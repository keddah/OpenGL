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

    void Update() { CheckInputs(); }
    
    glm::vec2 GetMouseDelta() const { return mouseDelta; }
    
    bool* GetMoveInputs() { return moveInputs; }
    bool JumpBtnDown() const { return jump; }
    bool CrouchBtnDown() const { return crouch; }
    
private:
    void CheckInputs();
    void ClearInputs();

    bool& rRunning;

    int screenWidth, screenHeight;
    
    bool moveInputs[4];
    glm::vec2 mousePos;
    glm::vec2 mouseDelta;

    bool lmb, rmb;

    bool jump, crouch;
};
