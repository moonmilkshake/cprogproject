#ifndef PLAYER_H
#define PLAYER_H
#include "Component.h"

namespace crane
{

    class Player : public Component
    {
    public:
        static Player *getInstance(int x, int y, int w, int h);
        ~Player();
        void draw() const override;
        void tick() override;
        void keyDown(const SDL_Event &) override;
    protected:
        Player(int x, int y, int w, int h);
    private:
		SDL_Texture* playerTexture;
        static Player* instance;
        int xPosition;
        int yPosition;
        int xVelocity;
        int yVelocity;
    };

}

#endif