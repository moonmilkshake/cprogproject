#ifndef PLAYER_H
#define PLAYER_H
#include "MovableSprite.h"
#include "GameEngine.h"

// Implementering till spelet som hanterar spelaren
using namespace crane;

    class Player : public MovableSprite
    {
    public:
        static Player *getInstance(int x, int y, int w, int h, std::string assetPath, GameEngine* engine);
        //~Player(); implementera om Player får egna medlemmar att städa bort
        void tick() override;
        void setAdaptToYPosition(bool adapt);
        void setAdaptFactorToYPosition(int newAdaptFactor);
    protected:
        Player(int x, int y, int w, int h, std::string assetPath, GameEngine* engine);
        void handleUpArrowKeyDownPress() override;
        void handleDownArrowKeyDownPress() override;
        void handleLeftArrowKeyDownPress() override;
        void handleRightArrowKeyDownPress() override;
        void handleWKeyDownPress() override;
        void handleAKeyDownPress() override;
        void handleSKeyDownPress() override;
        void handleDKeyDownPress() override;

        void handleWKeyRelease() override;
        void handleAKeyRelease() override;
        void handleSKeyRelease() override;
        void handleDKeyRelease() override;
    private:
        static Player* instance;
        int previousYPosition;
        int adaptFactorToYPosition;
        int xVelocity;
        int yVelocity;
        bool adaptToYPosition;
        GameEngine* engine;
    };

#endif