#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H
#include "Component.h"
#include <string>

namespace crane
{

    class MovableSprite : public Component
    {
    public:
        static MovableSprite *getInstance(int x, int y, int w, int h, std::string assetPath);
        ~MovableSprite();
        void handleCollision(const Component& other) override;
        int getCurrentX() const;
        int getCurrentY() const;
        void setSpeed(int newSpeed);
    protected:
        MovableSprite(int x, int y, int w, int h, std::string assetPath);
        void draw() const override;
        void tick() override;
        int speed;
    private:
        SDL_Texture* spriteTexture;
        int xPosition;
        int yPosition;
    };

}

#endif