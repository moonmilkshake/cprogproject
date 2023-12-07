#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Component.h"
#include <vector>

namespace crane {

    class GameEngine {
    public:
        void run();
        void addGameComponent(Component* component);
        void removeGameComponent(Component* component);
        void addUIComponent(Component* component);
        void removeUIComponent(Component* component);
        void startGame();
        void togglePause();
        void showPauseMenu();
        void hidePauseMenu();
        bool isGameRunning() const;
        GameEngine();
        ~GameEngine();

    private:
        std::vector<Component*> addedGameComponent;
        std::vector<Component*> addedUiComponent;
        std::vector<Component*> removed;
        std::vector<Component*> gameComponents;
        std::vector<Component*> uiComponents;
        bool gameRunning = false;
        bool gamePaused = false;
    };

}

#endif // GAMEENGINE_H
