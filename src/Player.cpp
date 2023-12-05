#include "Player.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace crane
{
    Player* Player::instance = nullptr;

    Player::Player(int x, int y, int w, int h) : Component(x, y, w, h)
    {
        // Hantera skapandet av Player, grafik etc
        playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png").c_str());
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
        SDL_RenderCopy(graphic.get_ren(), playerTexture, NULL, &getRect());
    }

    void Player::tick()
    {
        // Implementera hur klassen uppdateras varje frame
        const Uint8* keys = SDL_GetKeyboardState(NULL);

        if (keys[SDL_SCANCODE_UP])
        {
            // Move the player up
            setY(getY());
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            // Move the player down
            setY(getY());
        }
        if (keys[SDL_SCANCODE_LEFT])
        {
            // Move the player left
            setX(getX());
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            // Move the player right
            setX(getX());
        }

    }

}