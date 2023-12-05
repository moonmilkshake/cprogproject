#include "Component.h"

namespace crane
{

    Component::Component(int x, int y, int w, int h) : rect{x, y, w, h}
    {
    }

    Component::~Component()
    {
    }

}