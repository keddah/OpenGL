/**************************************************************************************************************
* Player Controller - Code
*
* The code file for the Player controller class. Responsible for reading player inputs using SDL.
*
* Created by Dean Atkinson-Walker 2024
***************************************************************************************************************/


#include "Controller.h"


Controller::Controller(bool& running) : rRunning(running)
{
	// Get the display mode of the primary monitor
	SDL_DisplayMode current;
	if (SDL_GetCurrentDisplayMode(0, &current) == 0)
	{
		screenWidth = current.w;
		screenHeight = current.h;
	}
	
	else
	{
		// Handle error
		SDL_Log("SDL_GetCurrentDisplayMode failed: %s", SDL_GetError());
	}
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
	sprint = keyState[SDL_SCANCODE_LSHIFT];
	reload = keyState[SDL_SCANCODE_R];
	
	int mouse_x, mouse_y;
	
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
			SDL_GetMouseState(&mouse_x, &mouse_y);
			mouseDelta = glm::vec2(mouse_x, mouse_y) - mousePos;
			
			mousePos.x = mouse_x;
			mousePos.y = mouse_y;

			// Check if the mouse is about to go off the screen
			if (mouse_x < 5 || mouse_x > screenWidth - 5 ||
				mouse_y < 5 || mouse_y > screenHeight - 5)
			{
				// Reset the mouse position to the center of the screen
				SDL_WarpMouseInWindow(nullptr, screenWidth / 2, screenHeight / 2);
				mousePos = {screenWidth / 2, screenHeight / 2};
			}
			else mousePos = {mouse_x, mouse_y};
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