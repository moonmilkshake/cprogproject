#ifndef BUTTON_H
#define BUTTON_H

#include "Component.h"
#include <SDL2/SDL.h>
#include <string>

namespace crane {

    class Button : public Component {
    public:
        Button(int x, int y, int w, int h, std::string upAssetPath, std::string downAssetPath);
        virtual ~Button();
        virtual void perform(Button* source) = 0;
        void mouseDown(const SDL_Event&) override;
        void mouseUp(const SDL_Event&) override;
        void draw() const override;

    protected:
        SDL_Texture* upIcon;
        SDL_Texture* downIcon;
        bool isDown = false;

    private:
        Button(const Button&) = delete;
        Button& operator=(const Button&) = delete;
    };

}

#endif
