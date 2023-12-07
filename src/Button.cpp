#include "Button.h"
#include <SDL2/SDL_ttf.h>
#include "Graphics.h"
#include <SDL2/SDL_image.h>
#include "Component.h"
#include "Constants.h"
#include <iostream>

namespace crane{
    Button::Button(int x, int y, int w, int h, std::string txt): Component(x, y, w, h) //Position x,y Bredd och Höjd w,h och en string i konstruktorn
    {
        SDL_Surface*surf = TTF_RenderText_Solid(graphic.get_font(), txt.c_str(), { 0,0,0 }); //renderar knappens text till SDL surface
        texture = SDL_CreateTextureFromSurface(graphic.get_ren(), surf); //Sen skapas texture från surface, som används för att visa knappens text. men vi har ingen text
        SDL_FreeSurface(surf);
        //TODO: Ändra så att knappbilen ligger i TempMain
        startIcon = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/3e1af784d6f5369.png").c_str() ); //rpresenterar knappen innan nedtryck
        downIcon = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "").c_str() ); //representerar knappen nedtryckt

    }

    Button::~Button() //Destruktor, städar upp och tar bort textures.
    {
        SDL_DestroyTexture(texture);
        SDL_DestroyTexture(startIcon);
        SDL_DestroyTexture(downIcon);
    }

    
    Button* Button::getInstance(int x, int y, int w, int h, std::string txt){ //en statisk factory funktion
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

    void Button::draw() const {
    // Render the button icon
    if (isDown) {
        if (downIcon != nullptr) {
            SDL_RenderCopy(graphic.get_ren(), downIcon, NULL, &getRect());
        }
    } else {
        if (startIcon != nullptr) {
            SDL_RenderCopy(graphic.get_ren(), startIcon, NULL, &getRect());
        }
    }

    // Render the button text
    if (texture != nullptr) {
        // Adjust the destination rectangle if necessary to position the text correctly
        SDL_Rect textRect = getRect();
        // You might want to adjust textRect here to position the text correctly
        SDL_RenderCopy(graphic.get_ren(), texture, NULL, &textRect);
    }
}



}
