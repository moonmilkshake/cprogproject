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
        void keyDown(const SDL_Event &) override;
        void keyUp(const SDL_Event &) override;
    protected:
        MovableSprite(int x, int y, int w, int h, std::string assetPath);
        void draw() const override;
        void tick() override;
        virtual void handleUpArrowKeyDownPress() {}
        virtual void handleDownArrowKeyDownPress() {}
        virtual void handleLeftArrowKeyDownPress() {}
        virtual void handleRightArrowKeyDownPress() {}
        virtual void handleWKeyDownPress() {}
        virtual void handleAKeyDownPress() {}
        virtual void handleSKeyDownPress() {}
        virtual void handleDKeyDownPress() {}

        virtual void handleWKeyRelease() {}
        virtual void handleAKeyRelease() {}
        virtual void handleSKeyRelease() {}
        virtual void handleDKeyRelease() {}
        int speed;
        
    private:
        SDL_Texture* spriteTexture;
        int xPosition;
        int yPosition;
    };

}

#endif