#pragma once 
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include "Entity.hpp"

class RendererWindow
{
public:
	RendererWindow(const char* p_title,int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	int getRefreshRate();
	void clear();
	void cleanUp();
	void render(Entity& p_entity);
	void display();
private:
	SDL_Window* window; 
	SDL_Renderer* renderer; 
};