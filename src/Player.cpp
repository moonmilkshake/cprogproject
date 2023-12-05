#include "Player.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace crane
{
    Player* Player::instance = nullptr;

    Player::Player(int x, int y, int w, int h) : Component(x, y, w, h)
    {
        // Hantera skapandet av Player, grafik etc
        playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png").c_str());
        xPosition = x;
        yPosition = y;
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

    void Player::draw() const
    {
        // Implementera hur klassen ritas ut
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
            yVelocity = -1;
            std::cout << "uppåt" << std::endl;

        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            // Move the player down
            yVelocity = 1;

        }
        if (keys[SDL_SCANCODE_LEFT])
        {
            // Move the player left
            xVelocity = -1;

        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            // Move the player right
            xVelocity = 1;
        }
    }

    void Player::tick()
    {
        // Implementera hur klassen uppdateras varje frame
        xPosition += xVelocity;
        yPosition += yVelocity;
        graphic.renderBackground(xPosition, yPosition);
    }

}