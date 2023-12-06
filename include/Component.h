#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

namespace crane
{
	class Component
	{
	public:
		virtual ~Component();
		virtual void mouseDown(const SDL_Event&) {}
        virtual void mouseUp(const SDL_Event&) {}
        virtual void keyDown(const SDL_Event&) {}
        virtual void keyUp(const SDL_Event&) {}
        virtual void draw() const = 0;
        virtual void tick() {}
		const SDL_Rect& getRect() const { return rect; }
		virtual bool checkCollision(const Component& other) const;
		void setCollided(bool newCollided);
		virtual void handleCollision(const Component& other) {}
	protected:
		Component(int x, int y, int w, int h);
		bool collided = false;
		SDL_Rect rect;
	private:
		Component(const Component&) = delete;
		const Component& operator=(const Component&) = delete;
	};
}

#endif
