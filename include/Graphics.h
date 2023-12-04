#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <string>

struct Graphics
{
    Graphics();
	~Graphics();

    SDL_Window* win; //pekare till SDL_window
    SDL_Renderer* ren; //pekare till SDL_Renderer
    Mix_Chunk* music; //pekare till SDL_mixer chunk;
};

extern Graphics graphic; //extern innebär att variabeln graphic är definierad någon annanstans.


#endif