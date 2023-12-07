#include "Component.h"

namespace crane
{

    Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
    {
    }

    bool Component::checkCollision(const Component* other) const
    {
        return SDL_HasIntersection(&getRect(), &other->getRect());
    }

    void Component::setCollided(bool newCollided) {
        collided = newCollided;
    }

    Component::~Component()
    {
    }

}