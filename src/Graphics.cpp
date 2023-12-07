#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>
#include "Component.h"

namespace crane
{

    Graphics::Graphics()
    {
        SDL_Init(SDL_INIT_EVERYTHING);
        // initialiserar SDL-biblioteket och aktiverar alla des delsystem, tex grafik, ljud
        win = SDL_CreateWindow("Game", 10, 10, 1000, 700, 0);
        // Skapar ett fönster med titel Game, placerat vid 10,10. och med dimensionerna 700x500 pixlar.
        // 0 representerar antal flaggor
        ren = SDL_CreateRenderer(win, -1, 0);
        // kopplad till fönstret, ansvarar för att rita grafik i fönstret.

        IMG_Init(IMG_INIT_PNG);

        //loadBackground(constants::gResPath + "images/BG_03.png");

        //Mix_OpenAudio(20050, AUDIO_S16SYS, 2, 4096);
        // anger ljudformat(16-bit), antalet kanaler(2 för stereo) och storleken på ljudbufferten (4096)
        //music = Mix_LoadWAV((constants::gResPath + "sounds/christmasPiano.mp3").c_str());
        //Mix_PlayChannel(-1, music, -1);
        // Spelar upp inladdade musiken, -1= använda första tillgängliga kanal, andra -1 == loopa musiken.
        SDL_GetWindowSizeInPixels(win, &screenWidth, &screenHeight);
    }

    void Graphics::setScreenSize(int newScreenWidth, int newScreenHeight)
    {
        screenWidth = newScreenWidth;
        screenHeight = newScreenHeight;
        SDL_SetWindowSize(win, screenWidth, screenHeight);
    }

    int Graphics::getScreenHeight() const
    {
        return screenHeight;
    }

    int Graphics::getScreenWidth() const
    {
        return screenWidth;
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

        //SDL_Rect destRect = { 0, 0, screenWidth, screenHeight };
        SDL_RenderCopy(ren, backgroundTexture, nullptr, nullptr);
    }



/**
    void Graphics::renderBackground(int xOffset, int yOffset) {
        int screenWidth, screenHeight;
        SDL_GetWindowSize(win, &screenWidth, &screenHeight);
        int widthZoom, heightZoom;
        widthZoom = 1.75 * screenWidth;
        heightZoom = 1.75 * screenHeight;
        if (xOffset >= widthZoom) {
            xOffset = widthZoom;
        } else if (xOffset <= 0) {
            xOffset = 0;
        }
        if (yOffset >= heightZoom) {
            yOffset = heightZoom;
        } else if (yOffset <= 0) {
            yOffset = 0;
        }

        SDL_Rect destRect = { -xOffset, -yOffset, widthZoom, heightZoom };
        SDL_RenderCopy(ren, backgroundTexture, nullptr, &destRect);
    }
    */

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