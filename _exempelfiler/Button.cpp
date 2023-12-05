#include "Constants.h"
#include "Button.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

namespace crane {

using namespace std;

Button::Button(int x, int y, int w, int h, string txt): Component(x,y,w,h)
{
    SDL_Surface* surf = TTF_RenderText_Solid(graphic.get_font(), txt.c_str(), { 0,0,0 }); //sista är färg. annars skapa text. 
    texture = SDL_CreateTextureFromSurface(graphic.get_ren(), surf);
    SDL_FreeSurface(surf); 
    //Här kan vi lägga till knappar. EXEMPEL:
    upIcon = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/bg.jpg").c_str());
}

Button::~Button()
{
    SDL_DestroyTexture(texture);
    SDL_DestroyTexture(upIcon);
}

Button* Button::getInstance(int x, int y, int w, int h, string txt) { // skapar en instans av Button
    return new Button(x, y, w, h, txt);
}

void Button::mouseDown(const SDL_Event& eve){
    SDL_Point p = { eve.button.x, eve.button.y};
    if (SDL_PointInRect(&p, &getRect()))
        isDown = true;
}

void Button::mouseUp(const SDL_Event& eve) {
    SDL_Point p = { eve.button.x , eve.button.y }; //Skapar en SDL_Point med x- och y-koordinaterna från musknappen som släpps 
                                 //(eve.button.x och eve.button.y). Detta representerar muspositionen vid knappens upptryckning.
    if (SDL_PointInRect(&p, &getRect()))
        perform(this); //Tror att this är pekaren till knappen. eller knappens pekare
    
    isDown = false;
}

void Button::draw() const {
    if (isDown)
        SDL_RenderCopy(graphic.get_ren(), upIcon, NULL, &getRect());
    else
        SDL_RenderCopy(graphic.get_ren(), upIcon, NULL, &getRect());
    
    SDL_RenderCopy(graphic.get_ren(), texture, NULL, &getRect());

}

    void Button::tick() {
        cout << "knapp tick" << endl;
        //Implementera hur klassen uppdateras varje frame
    }

}

