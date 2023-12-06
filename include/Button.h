#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace crane {

    class Button : public crane::Component {
    public:
        static Button* getInstance(int x, int y, int w, int h, std::string txt);
        virtual void perform(Button* source) {}
        ~Button();
        void mouseDown(const SDL_Event&) override;
        void mouseUp(const SDL_Event&) override;
        void draw() const override;
    protected:
        Button(int x, int y, int w, int h, std::string txt);

    private:
        std::string text;
        SDL_Texture* texture;
        SDL_Texture* startIcon;
        SDL_Texture* downIcon;
        bool isDown = false;
    };

}

#endif
