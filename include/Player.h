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
    protected:
        Player(int x, int y, int w, int h);
        void draw() const override;
        void tick() override;

    private:
		SDL_Texture* playerTexture;
        static Player* instance;
    };

}

#endif