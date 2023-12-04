#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

class Button : public Component
{
public:
    static Button* getInstance(int x, int y, int w, int h, std::string txt):
    void mouseDown(const SDL_Event&);
    void mouseUp(const SDL_Event&);
    void draw() const; //vi har draw för att knappen är något vi kommer rita ut
    virtual void perform(Button* source) {} //behövs för att kunna köra knappen
    ~Button();
protected:
    Button(int x, int y, int w, int h, std::string txt);
private:
    std::string text; //En privat medlemsvariabel som lagrar texten för knappen
    SDL_Texture* texture; //En privat medlemsfunktion som lagrar en SDL_Texture för knappen.
    //SDL_Texture* vårIcon. text uppKnapp.
    bool isDown = false; //Håller reda på om knappen är nedtryckt eller inte.
}

#endif