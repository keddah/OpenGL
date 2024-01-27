#pragma once

#include <vec2.hpp>

#include "SDL.h"

class Controller
{
public:
    Controller() = default;
    Controller(bool& running) : rRunning(running) { }
    ~Controller() = default;

    void Update();

    bool* GetMoveInputs() { return moveInputs; }
    bool JumpBtnDown() const { return jump; }
    bool CrouchBtnDown() const { return crouch; }
    
private:
    void CheckInputs();
    void ClearInputs();

    bool& rRunning;

    bool moveInputs[4];
    glm::vec2 mousePos;

    bool lmb, rmb;

    bool jump, crouch;
};
