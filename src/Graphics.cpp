#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL.h>

Graphics::Graphics(){
    SDL_Init(SDL_INIT_EVERYTHING);
    // initialiserar SDL-biblioteket och aktiverar alla des delsystem, tex grafik, ljud
    win = SDL_CreateWindow("Game", 10, 10, 700, 500, 0);
    // Skapar ett fönster med titel Game, placerat vid 10,10. och med dimensionerna 700x500 pixlar.
    //0 representerar antal flaggor
    ren = SDL_CreateRenderer(win, -1, 0);
    //kopplad till fönstret, ansvarar för att rita grafik i fönstret.
    Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
    //anger ljudformat(16-bit), antalet kanaler(2 för stereo) och storleken på ljudbufferten (4096)
    music = Mix_LoadWAV((constants::gResPath + "sounds/bgMusic.wav").c_str());
    Mix_PlayChannel(-1, music, -1);
    //Spelar upp inladdade musiken, -1= använda första tillgängliga kanal, andra -1 == loopa musiken.
}

Graphics::~Graphics(){
    Mix_FreeChunk(music);
    Mix_CloseAudio();
    SDL_DestroyWindow(win);
    SDL_DestroyRenderer(ren);
    SDL_Quit();
}

Graphics graphic;
