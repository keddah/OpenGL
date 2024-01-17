#include "Game.h"
#include "CustomTimer.h"

Game game;

int main()
{
	// Using this as the starting point of the delta time
	Time::SetCurrentTime(Time::GetElapsedTime());

	// Used for fixed update;
	float tickTimer = 0;

	while (true)
	{
		// The time that has to elapse in order for fixed update to tick.
		constexpr float timeStep = .0125f;

		Time::Update();
		const float deltaTime = Time::GetDeltaTime();

		game.Update(deltaTime);

		// When the timer elapses... do the fixed update.
		tickTimer += deltaTime;
		while (tickTimer > timeStep)
		{
			game.FixedUpdate(deltaTime);
			tickTimer = 0;
		}

		game.Render();
		Time::SetLastFrameTime();
	}

	return 0;
}

// Initially set values for the time.
float Time::deltaTime = 0;
float Time::elapsedGameTime = 0;
float Time::currentTime = 0;
float Time::newTime = 0;

int main()
{
	// Using this as the starting point of the delta time
	Time::SetCurrentTime(Time::GetElapsedTime());

	// Used for fixed update;
	float tickTimer = 0;
}