#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace crane
{

    Graphics::Graphics()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        // initialiserar SDL-biblioteket och aktiverar alla des delsystem, tex grafik, ljud
        win = SDL_CreateWindow("Game", 10, 10, 1000, 1000, 0);
        // Skapar ett fönster med titel Game, placerat vid 10,10. och med dimensionerna 700x500 pixlar.
        // 0 representerar antal flaggor
        ren = SDL_CreateRenderer(win, -1, 0);
        // kopplad till fönstret, ansvarar för att rita grafik i fönstret.

        IMG_Init(IMG_INIT_PNG);

        loadBackground(constants::gResPath + "images/BG_03.png");

        Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        // anger ljudformat(16-bit), antalet kanaler(2 för stereo) och storleken på ljudbufferten (4096)
        music = Mix_LoadWAV((constants::gResPath + "sounds/christmasPiano.mp3").c_str());
        Mix_PlayChannel(-1, music, -1);
        // Spelar upp inladdade musiken, -1= använda första tillgängliga kanal, andra -1 == loopa musiken.
    }

    void Graphics::loadBackground(const std::string& filePath) {
        backgroundTexture = loadTexture(filePath);
    }

    SDL_Texture* Graphics::loadTexture(const std::string& filePath) {
        SDL_Texture* texture = nullptr;
        SDL_Surface* surface = IMG_Load(filePath.c_str());
        if (surface != nullptr) {
            texture = SDL_CreateTextureFromSurface(ren, surface);
            SDL_FreeSurface(surface);
        }
        return texture;
    }

    void Graphics::renderBackground(int xOffset, int yOffset) {
        SDL_Rect destRect = { -xOffset, -yOffset, 2000, 1200 };
        SDL_RenderCopy(ren, backgroundTexture, nullptr, &destRect);
    }

    void Graphics::setCustomBackground(const std::string& filePath) {
        loadBackground(filePath);
    }

    SDL_Renderer* Graphics::get_ren() const {
		return ren;
	}

	TTF_Font* Graphics::get_font() const {
		return font;
	}

    Graphics::~Graphics()
    {
        Mix_FreeChunk(music);
        Mix_CloseAudio();
        SDL_DestroyWindow(win);
        SDL_DestroyRenderer(ren);
        SDL_Quit();
    }

    Graphics graphic;

}