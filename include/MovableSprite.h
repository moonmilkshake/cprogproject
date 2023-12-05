#ifndef MOVABLESPRITE_H
#define MOVABLESPRITE_H
#include "Component.h"

namespace crane
{

    class MovableSprite : public Component
    {
    public:
        static MovableSprite *getInstance(int x, int y, int w, int h);

    protected:
        MovableSprite(int x, int y, int w, int h);
        void draw() const override;
        void tick() override;
    };

}

#endif