#include "Player.h"
#include "Constants.h"
#include "Graphics.h"
#include "MovableSprite.h"
#include "ThrowableRock.h"
#include "GameEngine.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Implementering till spelet som hanterar spelaren
using namespace crane;

Player *Player::instance = nullptr;

Player::Player(int x, int y, int w, int h, std::string assetPath, GameEngine* engine) : MovableSprite(x, y, w, h, assetPath)
{
    // Hantera skapandet av Player, grafik etc
    // playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + assetPath).c_str());
    this->engine = engine;
    xVelocity = 0;
    yVelocity = 0;
    adaptToYPosition = false;
    adaptFactorToYPosition = 1;
    previousYPosition = rect.y;
}

// Player::~Player() implementera om Player får egna medlemmar att städa bort
//{
// SDL_DestroyTexture(playerTexture);
// }

// Hämta pekare till spelare, tillåter bara en instans av Player
Player *Player::getInstance(int x, int y, int w, int h, std::string assetPath, GameEngine* engine)
{
    if (!instance)
    {
        instance = new Player(x, y, w, h, assetPath, engine);
    }
    return instance;
}

void Player::tick()
{
    // Implementera hur klassen uppdateras varje frame

    if (collided)
    {
        if (xVelocity > 0)
        {
            xVelocity = -1;
        }
        else if (xVelocity < 0)
        {
            xVelocity = 1;
        }
        else if (yVelocity > 0)
        {
            yVelocity = -1;
        }
        else if (yVelocity)
        {
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

void Player::setAdaptToYPosition(bool adapt)
{
    adaptToYPosition = adapt;
}

void Player::setAdaptFactorToYPosition(int newAdaptFactor)
{
    adaptFactorToYPosition = newAdaptFactor;
}

void Player::handleUpArrowKeyDownPress()
{
    int spriteCenterX = static_cast<int>(rect.x + (rect.w / 2)); 
    int spriteCenterY = static_cast<int>(rect.y + (rect.h / 2)); 
    ThrowableRock* rock = ThrowableRock::getInstance(spriteCenterX, spriteCenterY, 15, 15, "up", "images/rock.png", engine);
}

void Player::handleDownArrowKeyDownPress()
{
    int spriteCenterX = static_cast<int>(rect.x + (rect.w / 2)); 
    int spriteCenterY = static_cast<int>(rect.y + (rect.h / 2)); 
    ThrowableRock* rock = ThrowableRock::getInstance(spriteCenterX, spriteCenterY, 15, 15, "down", "images/rock.png", engine);
}

void Player::handleLeftArrowKeyDownPress()
{
    int spriteCenterX = static_cast<int>(rect.x + (rect.w / 2)); 
    int spriteCenterY = static_cast<int>(rect.y + (rect.h / 2)); 
    ThrowableRock* rock = ThrowableRock::getInstance(spriteCenterX, spriteCenterY, 15, 15, "left", "images/rock.png", engine);
}

void Player::handleRightArrowKeyDownPress()
{
    int spriteCenterX = static_cast<int>(rect.x + (rect.w / 2)); 
    int spriteCenterY = static_cast<int>(rect.y + (rect.h / 2)); 
    ThrowableRock* rock = ThrowableRock::getInstance(spriteCenterX, spriteCenterY, 15, 15, "right", "images/rock.png", engine);
}

void Player::handleWKeyDownPress()
{
    yVelocity = -speed;
}

void Player::handleSKeyDownPress()
{
    yVelocity = speed;
}

void Player::handleAKeyDownPress()
{
    xVelocity = -speed;
}

void Player::handleDKeyDownPress()
{
    xVelocity = speed;
}

void Player::handleWKeyRelease()
{
    yVelocity = 0;
}

void Player::handleSKeyRelease()
{
    yVelocity = 0;
}

void Player::handleAKeyRelease()
{
    xVelocity = 0;
}

void Player::handleDKeyRelease()
{
    xVelocity = 0;
}