#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace crane
{

    struct Graphics
    {
    public:
        Graphics();
        ~Graphics();
        SDL_Renderer *get_ren() const;
        TTF_Font *get_font() const;
        SDL_Window *win;   // pekare till SDL_window
        SDL_Renderer *ren; // pekare till SDL_Renderer
        Mix_Chunk *music;  // pekare till SDL_mixer chunk;
        TTF_Font* font;    // pekare till font
        void loadBackground(const std::string& filepath);
        void renderBackground(int xOffset, int yOffset);
        void setCustomBackground(const std::string& filePath);
        SDL_Texture* backgroundTexture;
        SDL_Texture* loadTexture(const std::string& filePath);
    };

    extern Graphics graphic; // extern innebär att variabeln graphic är definierad någon annanstans.

}

#endif