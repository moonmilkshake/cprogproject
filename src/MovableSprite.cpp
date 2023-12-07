#include "MovableSprite.h"
#include "Constants.h"
#include "Graphics.h"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

//Klass för att hantera objekt på skärmen som inte rör på sig
namespace crane {

    MovableSprite::MovableSprite(int x, int y, int w, int h, std::string assetPath) : Component(x, y, w, h) {
        //Hantera skapandet av MovableSprite, grafik etc
        //spriteTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + "images/tempPlayer.png" + assetPath).c_str());
        spriteTexture = IMG_LoadTexture(graphic.get_ren(), (constants::gResPath + assetPath).c_str());
        speed = 3;

    }

	MovableSprite* MovableSprite::getInstance(int x, int y, int w, int h, std::string assetPath) {
		return new MovableSprite(x, y, w, h, assetPath);
	}

    void MovableSprite::draw() const {
		//Implementera hur klassen ritas ut
        SDL_RenderCopy(graphic.get_ren(), spriteTexture, NULL, &getRect());
	}

    void MovableSprite::tick() {
        //Implementera hur klassen uppdateras varje frame
    }

    void MovableSprite::handleCollision(const Component& other) 
    {
        
    }

    int MovableSprite::getCurrentX() const
    {
        return rect.x;
    }

    int MovableSprite::getCurrentY() const
    {
        return rect.y;
    }

    void MovableSprite::setSpeed(int newSpeed)
    {
        speed = newSpeed;
    }

    MovableSprite::~MovableSprite()
    {
        SDL_DestroyTexture(spriteTexture);
    }

}