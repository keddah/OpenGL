#pragma once
class Game
{
public:
	Game();

	void Update(float deltaTime);
	void FixedUpdate(float deltaTime);

	void Render();

private:
	void Init();
};

