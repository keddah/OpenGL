#include "Controller.h"


// void Controller::CheckInputs()
// {
//     SDL_Event e;
//     if (SDL_PollEvent(&e))
//     {
//         if (e.type == SDL_QUIT)
//         {
//             MANAGER::SetRunning(false);
//         }
//     }
// }


/**************************************************************************************************************
* Player Controller - Code
*
* The code file for the Player controller class. Responsible for reading player inputs using SDL.
*
* Created by Dean Atkinson-Walker 2023
***************************************************************************************************************/

void Controller::Update()
{
	CheckInputs();
}


void Controller::CheckInputs()
{
	const Uint8* keyState = SDL_GetKeyboardState(0);

	// Vertical inputs
	moveInputs[0] = keyState[SDL_SCANCODE_W] || keyState[SDL_SCANCODE_UP];
	moveInputs[1] = keyState[SDL_SCANCODE_S] || keyState[SDL_SCANCODE_DOWN];
	
	// Horizontal inputs
	moveInputs[2] = keyState[SDL_SCANCODE_A] || keyState[SDL_SCANCODE_LEFT];
	moveInputs[3] = keyState[SDL_SCANCODE_D] || keyState[SDL_SCANCODE_RIGHT];

	jump = keyState[SDL_SCANCODE_SPACE];
	crouch = keyState[SDL_SCANCODE_LCTRL];
	
	int mouse_x, mouse_y;
	SDL_GetMouseState(&mouse_x, &mouse_y);
	mousePos.x = mouse_x;
	mousePos.y = mouse_y;
	
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch (e.type)
		{
		case SDL_MOUSEBUTTONDOWN:
			if(e.button.button == SDL_BUTTON_LEFT) lmb = true;
			if(e.button.button == SDL_BUTTON_RIGHT) rmb = true;
			break;
	
		case SDL_MOUSEBUTTONUP:
			if(e.button.button == SDL_BUTTON_LEFT) lmb = false;
			if(e.button.button == SDL_BUTTON_RIGHT) rmb = false;
			break;
	
		case SDL_MOUSEMOTION:
			if(e.button.button == SDL_BUTTON_LEFT) lmb = true;
			if(e.button.button == SDL_BUTTON_RIGHT) rmb = true;
			break;
			
			// When alt + F4 is pressed.
		case SDL_QUIT:
			rRunning = false;
			break;
	
		case SDL_KEYDOWN:
			// Toggle pause down
			// if(e.key.keysym.scancode == SDL_SCANCODE_ESCAPE || e.key.keysym.scancode == SDL_SCANCODE_P) pauseDown = !pauseDown;
			break;
		}
			
	}
}

void Controller::ClearInputs()
{
	// wheelUp = false;
	// wheelDown = false;
	//
	// num1 = false;
	// num2 = false;
	// num3 = false;
	// // num4 = false;
	//
	// for (bool& moveInput : moveInputs) moveInput = false;
}