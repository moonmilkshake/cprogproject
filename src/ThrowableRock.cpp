#include "ThrowableRock.h"
#include "Constants.h"
#include "Graphics.h"
#include "MovableSprite.h"
#include "GameEngine.h"
#include "Player.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

// Implementering till spelet som hanterar spelaren
using namespace crane;

ThrowableRock::ThrowableRock(int x, int y, int w, int h, std::string trajectory, std::string assetPath, GameEngine* engine) : MovableSprite(x, y, w, h, assetPath)
{
    // Hantera skapandet av Player, grafik etc
    // playerTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + assetPath).c_str());
    this->engine = engine;
    xVelocity = 0;
    yVelocity = 0;
    previousYPosition = rect.y;
    this->trajectory = trajectory;
    engine->addGameComponent(this);
}

// ThrowableRock::~ThrowableRock() implementera om ThrowableRock får egna medlemmar att städa bort
//{

// }

// Hämta pekare till spelare, tillåter bara en instans av Player
ThrowableRock *ThrowableRock::getInstance(int x, int y, int w, int h, std::string trajectory, std::string assetPath, GameEngine* engine)
{
    return new ThrowableRock(x, y, w, h, trajectory, assetPath, engine);
}

void ThrowableRock::tick()
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
    windowHeight = graphic.getScreenHeight();
    windowWidth = graphic.getScreenWidth();

    //Koll om stenen lämnar skärmen
    if (rect.x < 0 || rect.y > windowHeight || rect.y < 0 || rect.x > windowWidth)
    {
        engine->removeGameComponent(this);
    } else {
        if (trajectory == "up") {
            rect.y -= 10;
        } else if (trajectory == "down") {
            rect.y += 10;
        } else if (trajectory == "left") {
            rect.x -= 10;
        } else if (trajectory == "right") {
            rect.x += 10;
        }
    }

    collided = false;
}

void ThrowableRock::handleCollision(const Component* other)
{
    const Player* playerPtr = dynamic_cast<const Player*>(other);
    if (playerPtr == nullptr) {
        engine->removeGameComponent(this);
    }
}

