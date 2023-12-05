#include "GameEngine.h"
#include <SDL2/SDL.h>
#include "Component.h"
#include "Graphics.h"

using namespace std;

namespace crane 
{

#define FPS 60

void GameEngine::add(Component* component) {
    added.push_back(component);
}

void GameEngine::remove(Component* component) {
    removed.push_back(component);
}

void GameEngine::run() {
    //Implementera spelloopen

    bool quit = false;
    Uint32 tickInterval = 1000 / FPS; //Räkna ut millisekunder mellan varje frame
    while (!quit) {
        Uint32 nextTick = SDL_GetTicks() + tickInterval; //Räkna ut när nästa frame ska visas i millisekunder
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                //Implementera varje case
                case SDL_QUIT: 
                    quit = true; 
                    break;
                case SDL_KEYUP:
					for (Component* c : components) {
						c->keyUp(event);
                    }
                    break;
                case SDL_KEYDOWN:
                    for (Component* c : components) {
						c->keyDown(event);
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
					for (Component* c : components) {
						c->mouseDown(event);
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
					for (Component* c : components) {
						c->mouseUp(event);
                    }
                    break;


            } //switch

        } //while PollEvent 

		for (Component* c : components) { //Gå igenom varje komponent och uppdatera dem vardera frame
			c->tick();
        }

        for (Component* c : added) { //Lägg till komponenter som har tillkommit i detta varv av loopen
            components.push_back(c);
        }
        added.clear();

        for (Component* c : removed) { //Ta bort komponenter som ska bort detta varv
            for (vector<Component*>::iterator i = components.begin(); i != components.end();) 
            {
                if (*i == c) {
                    i = components.erase(i);
                } else {
                    i++;
                }
            }
        }
        removed.clear();

        SDL_SetRenderDrawColor(graphic.ren, 255, 255, 255, 255); //Sätter färgen att rendera med till vit
        SDL_RenderClear(graphic.ren); //tömmer renderaren (med färgen vit?)

        for (Component* c : components) { //Rita ut alla komponenter
            c->draw();
        }
        SDL_RenderPresent(graphic.ren); //Presentera frame:en på skärmen

        int delay = nextTick - SDL_GetTicks(); //Räkna ut tiden i millisekunder krav tills nästa frame ska visas
        if (delay > 0) { //Fördröj loopen om frame:en inte ska visas än
            SDL_Delay(delay);
        }
    } //while !quit
}

    GameEngine::~GameEngine() {}

}