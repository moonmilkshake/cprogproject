#include "ImmovableSprite.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Klass för att hantera objekt på skärmen som inte rör på sig
namespace crane {

    ImmovableSprite::ImmovableSprite(int x, int y, int w, int h) : Component(x, y, w, h) {
        //Hantera skapandet av ImmovableSprite, grafik etc

    }

	ImmovableSprite* ImmovableSprite::getInstance(int x, int y, int w, int h) {
		return new ImmovableSprite(x, y, w, h);
	}

    void ImmovableSprite::draw() const {
		//Implementera hur klassen ritas ut
	}

    void ImmovableSprite::tick() {
        //Implementera hur klassen uppdateras varje frame
    }

}