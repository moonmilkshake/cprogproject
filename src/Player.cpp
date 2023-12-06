#include "Player.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Klass som hanterar spelaren på skärmen
namespace crane
{
    Player *Player::instance = nullptr;

    Player::Player(int x, int y, int w, int h) : Component(x, y, w, h)
    {
        // Hantera skapandet av Player, grafik etc
        playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png").c_str());
        xPosition = x;
        yPosition = y;
        xVelocity = 0;
        yVelocity = 0;
        speed = 3;
        adaptToYPosition = false;
        adaptFactorToYPosition = 1;
        previousYPosition = rect.y;
    }

    Player::~Player()
    {
        SDL_DestroyTexture(playerTexture);
    }

    // Hämta pekare till spelare, tillåter bara en instans av Player
    Player *Player::getInstance(int x, int y, int w, int h)
    {
        if (!instance)
        {
            instance = new Player(x, y, w, h);
        }
        return instance;
    }

    // Ritar ut spelaren på kartan och anpassar kartan i förhållande till spelarens koordinater
    void Player::draw() const
    {
        // const SDL_Rect &rect = getRect();
        // graphic.renderBackground(xPosition, yPosition);
        SDL_RenderCopy(graphic.get_ren(), playerTexture, NULL, &getRect());
    }

    void Player::keyDown(const SDL_Event &eve)
    {
        const Uint8 *keys = SDL_GetKeyboardState(NULL);

        // Hantera piltangenterna på tangentbordet
        if (keys[SDL_SCANCODE_UP])
        {
            yVelocity = -speed;
        }
        if (keys[SDL_SCANCODE_DOWN])
        {
            yVelocity = speed;
        }
        if (keys[SDL_SCANCODE_LEFT])
        {
            xVelocity = -speed;
        }
        if (keys[SDL_SCANCODE_RIGHT])
        {
            xVelocity = speed;
        }
    }

    void Player::keyUp(const SDL_Event &eve)
    {
        switch (eve.key.keysym.sym)
        {
        case SDLK_UP:
        case SDLK_DOWN:
            yVelocity = 0;
            break;
        case SDLK_LEFT:
        case SDLK_RIGHT:
            xVelocity = 0;
            break;
        }
    }

    void Player::tick()
    {
        // Implementera hur klassen uppdateras varje frame

        if (collided)
        {
            if (xVelocity > 0)
            {
                xVelocity = -1;
            } else if (xVelocity < 0) {
                xVelocity = 1;
            }
            else if (yVelocity > 0)
            {
                yVelocity = -1;
            } else if (yVelocity) {
                yVelocity = 1;
            }
        }

        int windowWidth, windowHeight;
        SDL_GetWindowSize(graphic.win, &windowWidth, &windowHeight);

        // Kolla om spelaren försöker gå utanför rutans koordinater
        if (rect.x < 0)
        {
            rect.x = 0;
        }
        if (rect.y < 0)
        {
            rect.y = 0;
        }
        if (rect.x + rect.w > windowWidth)
        {
            rect.x = windowWidth - rect.w;
        }
        if (rect.y + rect.h > windowHeight)
        {
            rect.y = windowHeight - rect.h;
        }

        // uppdatera spelarens position
        rect.x += xVelocity;
        rect.y += yVelocity;

        // Minska/öka spelarens storlek baserat på om den går upp eller ner på skärmen
        if (adaptToYPosition)
        {
            if (rect.y > previousYPosition + 5)
            {
                rect.w += adaptFactorToYPosition;
                rect.h += adaptFactorToYPosition;
                previousYPosition = rect.y;
            }
            else if (rect.y < previousYPosition - 5)
            {
                if (rect.w > 5)
                {
                    rect.w -= adaptFactorToYPosition;
                    rect.h -= adaptFactorToYPosition;
                    previousYPosition = rect.y;
                }
            }
        }

        collided = false;
    }

    int Player::getPlayerX() const
    {
        return xPosition;
    }

    int Player::getPlayerY() const
    {
        return yPosition;
    }

    void Player::setSpeed(int newSpeed)
    {
        speed = newSpeed;
    }

    void Player::setAdaptToYPosition(bool adapt)
    {
        adaptToYPosition = adapt;
    }

    void Player::setAdaptFactorToYPosition(int newAdaptFactor)
    {
        adaptFactorToYPosition = newAdaptFactor;
    }

}