#ifndef PLAYER_H
#define PLAYER_H
#include "MovableSprite.h"

// Implementering till spelet som hanterar spelaren
using namespace crane;

    class Player : public MovableSprite
    {
    public:
        static Player *getInstance(int x, int y, int w, int h, std::string assetPath);
        //~Player(); implementera om Player får egna medlemmar att städa bort
        //void draw() const override;
        void tick() override;
        void keyDown(const SDL_Event &) override;
        void keyUp(const SDL_Event &) override;
        void setAdaptToYPosition(bool adapt);
        void setAdaptFactorToYPosition(int newAdaptFactor);
    protected:
        Player(int x, int y, int w, int h, std::string assetPath);
    private:
        static Player* instance;
        int previousYPosition;
        int adaptFactorToYPosition;
        int xVelocity;
        int yVelocity;
        bool adaptToYPosition;
    };

#endif