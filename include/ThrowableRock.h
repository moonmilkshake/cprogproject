#ifndef THROWABLEROCK_H
#define THROWABLEROCK_H
#include "MovableSprite.h"
#include "GameEngine.h"

// Implementering till spelet som hanterar spelaren
using namespace crane;

    class ThrowableRock : public MovableSprite
    {
    public:
        static ThrowableRock *getInstance(int x, int y, int w, int h, std::string trajectory, std::string assetPath, GameEngine* engine);
        //~Player(); implementera om Player får egna medlemmar att städa bort
        void tick() override;
        void handleCollision(const Component* other) override;
    protected:
        ThrowableRock(int x, int y, int w, int h, std::string trajectory, std::string assetPath, GameEngine* engine);
    private:
        GameEngine* engine;
        int previousYPosition;
        int xVelocity;
        int yVelocity;
        std::string trajectory;
    };

#endif