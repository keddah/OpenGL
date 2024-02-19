#include "Player.h"

Player::Ui::Ui(Player* player) : rPlayer(*player)
{
    if(TTF_Init() < 0)
    {
        print("Couldn't init")
        print(TTF_GetError())
        return;
    }

    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    
    const glm::vec2 screenSize = {dm.w, dm.h};

    ammoRenderer = new TextRenderer("9 || 45", "Fonts/Quicksand-Regular.ttf", 80);
    scoreRenderer = new TextRenderer(" Score:  0 ", "Fonts/Oxygen-Regular.ttf", 30);
    crosshair = new ImageRenderer("Images/crosshair.png");
    
    ammoRenderer->SetScreenSize(screenSize);
    scoreRenderer->SetScreenSize(screenSize);
    crosshair->SetScreenSize(screenSize);
    
    constexpr short ammoPadding = 20;
    ammoRenderer->SetDrawPosition(screenSize.x - ammoRenderer->GetDrawSize().x - ammoPadding, ammoPadding);
    ammoRenderer->SetDrawColour(199, 182, 165, 255);
    
    constexpr short scorePadding = 10;
    scoreRenderer->SetDrawPosition(scorePadding, screenSize.y - scoreRenderer->GetDrawSize().y - scorePadding);
    scoreRenderer->SetDrawColour(165, 189, 199, 255);

    // The center of the screen
    crosshair->SetDrawPosition(screenSize.x / 2 - crosshair->GetDrawSize().x / 2, screenSize.y / 2 - crosshair->GetDrawSize().y / 2);
}

void Player::Ui::Draw() const
{
    AmmoCount();
    ScoreCount();

    // Don't show the crosshair if adsing 
    if(!rPlayer.controller.RmbDown()) crosshair->Draw();
}

void Player::Ui::AmmoCount() const
{
    const short mag = rPlayer.wc.GetCurrentMag();
    const short reserve = rPlayer.wc.GetCurrentAmmo();

    const string output = to_string(mag) + " || " + to_string(reserve);
    
    ammoRenderer->Draw(output);
}

void Player::Ui::ScoreCount() const
{
    const int numHits = rPlayer.wc.GetHits();
    const string output = " Score:  " + to_string(numHits) + " ";
    scoreRenderer->Draw(output);
}
