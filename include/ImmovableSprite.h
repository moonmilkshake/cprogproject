#ifndef IMMOVABLESPRITE_H
#define IMMOVABLESPRITE_H
#include "Component.h"

namespace crane
{

    class ImmovableSprite : public Component
    {
    public:
        static ImmovableSprite *getInstance(int x, int y, int w, int h);

    protected:
        ImmovableSprite(int x, int y, int w, int h);
        void draw() const override;
        void tick() override;
    };

}

#endif