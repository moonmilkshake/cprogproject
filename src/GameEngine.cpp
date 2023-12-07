#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "Graphics.h"
#include <vector>
#include "Component.h"
#include <iostream>

using namespace std;
using namespace crane;

#define FPS 60

GameEngine::GameEngine() : gameRunning(false) //spelet startas inte direkt
{
    // Initialize any necessary game engine state here
}

void GameEngine::addGameComponent(Component *component) //tillåter oss lägga in game components, tex stenar osv
{
    addedGameComponent.push_back(component);
}

void GameEngine::removeGameComponent(Component *component)
{
    removed.push_back(component);
}

void GameEngine::addUIComponent(Component *component) //tillåter oss lägga in UIcomponent, text knappar, healthbar 
{
    addedUiComponent.push_back(component);
}

void GameEngine::removeUIComponent(Component *component)
{
    auto it = std::find(uiComponents.begin(), uiComponents.end(), component);
    if (it != uiComponents.end())
    {
        uiComponents.erase(it);
        // Consider managing memory here if necessary
    }
    removed.push_back(component);
}

void GameEngine::startGame()
{
    gameRunning = true;
}

bool GameEngine::isGameRunning() const
{
    return gameRunning;
}

void GameEngine::togglePause() 
{
    gamePaused = !gamePaused;
    // Additional logic to handle the game's paused state
}

void GameEngine::run()
{
    bool quit = false;
    Uint32 tickInterval = 1000 / FPS;
    // gameRunning = true;

    while (!quit)
    {
        Uint32 nextTick = SDL_GetTicks() + tickInterval;
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT) 
            {
                quit = true;
            }

            //Försök på implementera pause med esc:
            if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            {
                togglePause();
                continue;
            }

            // Hanterar tangenttryck på gamecomponents, tex player movement
            //TODO: lägg till alla knappar vi vill ha
            if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
            {
                for (Component *c : gameComponents)
                {
                    if (event.type == SDL_KEYDOWN)
                    {
                        c->keyDown(event);
                    }
                    else if (event.type == SDL_KEYUP)
                    {
                        c->keyUp(event);
                    }
                }
            }

            // Hanterar Musklick på UIcomponents, knappar
            for (Component *c : uiComponents)
            {
                if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    c->mouseDown(event);
                }
                else if (event.type == SDL_MOUSEBUTTONUP)
                {
                    c->mouseUp(event);
                }
            }
        }

        // Om spelet körs, uppdatera gameComponents
        if (isGameRunning() && !gamePaused)
        {
            for (Component *c : gameComponents)
            {
                c->tick();
            }
        }

        //Om spelet inte körs, uppdatera UIcomponents.
        //if (!isGameRunning())
        //{
            for (Component *c : uiComponents)
            {
                c->tick();
            }
        //}

        if (gamePaused)
        {
            /*
            showPauseMenu();
        } else {
            hidePauseMenu();
            */
        }

        //Ser till att UIComponent är uppdaterad 
        for (Component *c : addedUiComponent)
        {
            uiComponents.push_back(c);
        }
        addedUiComponent.clear();

        //Ser till att GameComponent är uppdaterad
        for (Component *c : addedGameComponent)
        {
            gameComponents.push_back(c);
        }
        addedGameComponent.clear();

        //Ta bort components
        for (Component *c : removed)
        {
            auto removeComponent = [&c](vector<Component *> &components)
            {
                auto it = std::find(components.begin(), components.end(), c);
                if (it != components.end())
                {
                    components.erase(it);
                    // Consider managing memory here if necessary
                }
            };
            removeComponent(gameComponents);
            removeComponent(uiComponents);
        }
        removed.clear();

        // Render the frame
        SDL_SetRenderDrawColor(graphic.get_ren(), 255, 255, 255, 255);
        SDL_RenderClear(graphic.get_ren());

        // Render background
        graphic.renderBackground(0, 0);

        // Render UI components if the game is not running
        if (!isGameRunning())
        {
            for (Component *c : uiComponents)
            {
                c->draw();
            }
        }

        // Render game components if the game is running
        if (isGameRunning())
        {
            for (Component *c : gameComponents)
            {
                c->draw();
            }
        }

        SDL_RenderPresent(graphic.get_ren());

        // Delay to maintain frame rate
        int delay = nextTick - SDL_GetTicks();
        if (delay > 0)
        {
            SDL_Delay(delay);
        }
    }
}

GameEngine::~GameEngine()
{
    // Rensar dynamiskt allokerat minne
    for (auto c : gameComponents)
    {
        delete c;
    }
    for (auto c : uiComponents)
    {
        delete c;
    }
}
