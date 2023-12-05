#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Component.h"
#include <vector>

namespace crane {

class GameEngine
{
    public:
        void run();
        void add(Component* component);
        void remove(Component* component);
        ~GameEngine();
    private:
        std::vector<Component*> components;
        std::vector<Component*> added;
        std::vector<Component*> removed;
};

}
#endif