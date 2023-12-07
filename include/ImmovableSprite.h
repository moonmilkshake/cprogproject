#ifndef IMMOVABLESPRITE_H
#define IMMOVABLESPRITE_H
#include "Component.h"
#include <string>

namespace crane
{

    class ImmovableSprite : public Component
    {
    public:
        static ImmovableSprite *getInstance(int x, int y, int w, int h, std::string assetPath);
        ~ImmovableSprite();
        void handleCollision(const Component* other) override;
    protected:
        ImmovableSprite(int x, int y, int w, int h, std::string assetPath);
        void draw() const override;
        void tick() override;
    private:
        SDL_Texture* spriteTexture;
    };

}

#endif