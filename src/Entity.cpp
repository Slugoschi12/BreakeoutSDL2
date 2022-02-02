#include "Entity.hpp"
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

Entity::Entity(float p_x, float p_y, float size_w, float size_h, SDL_Texture* p_tex)
:x(p_x), y(p_y), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = size_w;
	currentFrame.h = size_h;

}

float Entity::getX()
{
	return x;
}
float Entity::getY()
{
	return y;
}
float Entity::getW()
{
	return currentFrame.w;
}

float Entity::getH()
{
	return currentFrame.h;
}
float Entity::setX(float new_x)
{
	return x = new_x;
}
float Entity::setY(float new_y)
{
	return y = new_y;
}

SDL_Texture* Entity::getTex()
{
	return tex;
}

SDL_Rect Entity::getCurrentFrame()
{
	return currentFrame;
}
