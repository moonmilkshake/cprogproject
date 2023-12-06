#ifndef LABEL_H
#define LABEL_H

#include "Component.h"
#include <string>
#include <SDL2/SDL.h>

namespace crane {

    class Label : public crane::Component {
    public:
        static Label* getInstance(int x, int y, int w, int h, std::string txt);
        Label(int x, int y, int w, int h, const std::string& txt);
        void draw() const override;
        std::string getText() const;
        void setText(std::string newText);
        ~Label();
    private:
        std::string text;
        SDL_Texture* texture;
    };

}

#endif
