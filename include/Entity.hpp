#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class Entity
{	
public:
	Entity(float p_x, float p_y, float size_w, float size_h, SDL_Texture* p_tex);
	float getX();
	float getY();
	float setX(float new_x);
	float setY(float new_y);
	float getW();
	float getH();
	SDL_Rect getCurrentFrame();
	SDL_Texture* getTex();

private:
	float x, y;
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};