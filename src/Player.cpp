#include "Player.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

//Klass som hanterar spelaren på skärmen
namespace crane
{
    Player* Player::instance = nullptr;

    Player::Player(int x, int y, int w, int h) : Component(x, y, w, h)
    {
        // Hantera skapandet av Player, grafik etc
        playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png").c_str());
        xPosition = x;
        yPosition = y;
        xVelocity = 0;
        yVelocity = 0;
    }

    Player::~Player()
    {
        SDL_DestroyTexture(playerTexture);
    }

    Player *Player::getInstance(int x, int y, int w, int h)
    {
        if (!instance)
        {
            instance = new Player(x, y, w, h);
        }
        return instance;
    }

    //Ritar ut spelaren på kartan och anpassar kartan i förhållande till spelarens koordinater
    void Player::draw() const
    {
        graphic.renderBackground(xPosition, yPosition);
        SDL_RenderCopy(graphic.get_ren(), playerTexture, NULL, &getRect());
    }

    void Player::keyDown(const SDL_Event& eve)
    {
        const Uint8* keys = SDL_GetKeyboardState(NULL);
        xVelocity = 0;
        yVelocity = 0;

        if (keys[SDL_SCANCODE_UP])
        {
            // Move the player up
            yVelocity = -10;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            // Move the player down
            yVelocity = 10;
        }
        if (keys[SDL_SCANCODE_LEFT])
        {
            // Move the player left
            xVelocity = -10;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            // Move the player right
            xVelocity = 10;
        }
    }

    void Player::tick()
    {
        // Implementera hur klassen uppdateras varje frame
        xPosition += xVelocity;
        yPosition += yVelocity;
        xVelocity = 0;
        yVelocity = 0;
    }

    int Player::getPlayerX() const {
        return xPosition;
    }

    int Player::getPlayerY() const {
        return yPosition;
    }

}