#include "MovableSprite.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

namespace crane {

    MovableSprite::MovableSprite(int x, int y, int w, int h) : Component(x, y, w, h) {
        //Hantera skapandet av MovableSprites, grafik etc

    }

	MovableSprite* MovableSprite::getInstance(int x, int y, int w, int h) {
		return new MovableSprite(x, y, w, h);
	}

    void MovableSprite::draw() const {
		//Implementera hur klassen ritas ut
	}

    void MovableSprite::tick() {
        //Implementera hur klassen uppdateras varje frame
    }

}