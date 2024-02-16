#include "Player.h"

Player::Ui::Ui(Player* player) : rPlayer(*player)
{
    if(TTF_Init() == -1)
    {
        print("Couldn't init")
        print(TTF_GetError)
        return;
    }
    
    ammoRenderer.SetFontSize(16);
    ammoRenderer.SetDrawPosition(600, 600);

    scoreRenderer.SetFontSize(12);
    scoreRenderer.SetDrawPosition(-.95f, -.95f);
}

void Player::Ui::Draw() const
{
    // scoreRenderer.Draw(rPlayer.cam->GetProjectionMatrix());
    ammoRenderer.Draw(rPlayer.cam->GetProjectionMatrix());
}

void Player::Ui::Update(float deltaTime)
{
    AmmoCount();
    // ScoreCount();
}

void Player::Ui::AmmoCount()
{
    const short mag = rPlayer.wc.GetCurrentMag();
    const short reserve = rPlayer.wc.GetCurrentAmmo();

    const string output = to_string(mag) + " || " + to_string(reserve);
    ammoRenderer.SetText(output, "Fonts/Quicksand-Regular.ttf");
}

void Player::Ui::ScoreCount()
{
    const int numHits = rPlayer.wc.GetHits();
    const string output = "Targets Destroyed:  " + to_string(numHits);
    // ammoRenderer.SetText(output, "Fonts/Quicksand-Regular.ttf");
}
