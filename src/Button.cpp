#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include "Graphics.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Constants.h"
#include <iostream>

namespace crane{
    Button::Button(int x, int y, int w, int h, std::string upAssetPath, std::string downAssetPath) : Component(x, y, w, h), upIcon(nullptr), downIcon(nullptr), isDown(false) {
        upIcon = IMG_LoadTexture(graphic.get_ren(), upAssetPath.c_str());
        if (!upIcon) {
            std::cerr << "Failed to load texture: " << upAssetPath << " SDL_image Error: " << IMG_GetError() << std::endl;
        }
        // If you have a different image for the down state, load it here
        downIcon = IMG_LoadTexture(graphic.get_ren(), downAssetPath.c_str());
        if (!downIcon) {
            std::cerr << "Failed to load texture: " << upAssetPath << " SDL_image Error: " << IMG_GetError() << std::endl;
        }
    }

    Button::~Button() {
        SDL_DestroyTexture(upIcon);
        SDL_DestroyTexture(downIcon);
    }

    void Button::mouseDown(const SDL_Event& event) {
        SDL_Point p = { event.button.x, event.button.y };
        if (SDL_PointInRect(&p, &getRect())) {
            isDown = true;
        }
    }

    void Button::mouseUp(const SDL_Event& event) {
        SDL_Point p = { event.button.x, event.button.y };
        if (SDL_PointInRect(&p, &getRect())) {
            perform(this);
            isDown = false;
        }
    }

    void Button::draw() const {
        SDL_SetRenderDrawColor(graphic.get_ren(), 255, 0, 0, 255); // Red color
        SDL_RenderFillRect(graphic.get_ren(), &getRect());
        
        SDL_Texture* icon = isDown && downIcon ? downIcon : upIcon;
        if (icon != nullptr) {
            SDL_RenderCopy(graphic.get_ren(), icon, NULL, &getRect());
        }
    }
}
