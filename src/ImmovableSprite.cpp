#include "ImmovableSprite.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Klass för att hantera objekt på skärmen som inte rör på sig
namespace crane {

    ImmovableSprite::ImmovableSprite(int x, int y, int w, int h, std::string assetPath) : Component(x, y, w, h) {
        //Hantera skapandet av ImmovableSprite, grafik etc
        //spriteTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png" + assetPath).c_str());
        spriteTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + assetPath).c_str());

    }

	ImmovableSprite* ImmovableSprite::getInstance(int x, int y, int w, int h, std::string assetPath) {
		return new ImmovableSprite(x, y, w, h, assetPath);
	}

    void ImmovableSprite::draw() const {
		//Implementera hur klassen ritas ut
        SDL_RenderCopy(graphic.get_ren(), spriteTexture, NULL, &getRect());
	}

    void ImmovableSprite::tick() {
        //Implementera hur klassen uppdateras varje frame
    }

    void ImmovableSprite::handleCollision(const Component& other) 
    {
        
    }

    ImmovableSprite::~ImmovableSprite()
    {
        SDL_DestroyTexture(spriteTexture);
    }

}