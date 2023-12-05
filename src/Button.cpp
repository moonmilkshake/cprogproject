#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include "Graphics.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Constants.h"

namespace crane{
    Button::Button(int x, int y, int w, int h, std::string txt): Component(x, y, w, h)
    {
        SDL_Surface*surf = TTF_RenderText_Solid(graphic.get_font(), txt.c_str(), { 0,0,0 });
        texture = SDL_CreateTextureFromSurface(graphic.get_ren(), surf);
        SDL_FreeSurface(surf);
        upIcon = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + ".png").c_str() );
    }


    Button::~Button()
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(upIcon);
    }

    Button* Button::getInstance(int x, int y, int w, int h, std::string txt){
        return new Button(x, y, w, h, txt);
    }

    void Button::mouseDown(const SDL_Event& eve){
        SDL_Point p = { eve.button.x, eve.button.y};
        if (SDL_PointInRect(&p, &getRect()))
           isDown = true;
    }

    void Button::mouseUp(const SDL_Event& eve){
        SDL_Point p = { eve.button.x, eve.button.y};
        if (SDL_PointInRect(&p, &getRect()))
            perform(this);
            
        isDown = false;
    }

    void Button::draw() const{
        if (isDown)
            SDL_RenderCopy(graphic.get_ren(), upIcon, NULL, &getRect());

        SDL_RenderCopy(graphic.get_ren(), texture, NULL, &getRect());

    }

}
