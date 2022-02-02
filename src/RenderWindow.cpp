#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
using namespace std;

#include "RenderWindow.hpp"


RendererWindow::RendererWindow(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title,SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,p_w,p_h,SDL_WINDOW_SHOWN);//creaza fereastra

	if (window == NULL)
	{
		cout << "Window failed to init. Error: " << SDL_GetError() << endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);//(destinatie,index cate driver grafic )
}
SDL_Texture* RendererWindow::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL )
	{
		cout << "Failed to load texture. Error: " << SDL_GetError() << endl;
	}

	return texture;

}

void RendererWindow::clear()
{
	SDL_RenderClear(renderer);
}

void RendererWindow::render( Entity& p_entity )
{	
	SDL_Rect src;
	src.x = p_entity.getCurrentFrame().x;
	src.y = p_entity.getCurrentFrame().y;
	src.w = p_entity.getCurrentFrame().w;
	src.h = p_entity.getCurrentFrame().h;
	SDL_Rect dst;
	dst.x = p_entity.getX();
	dst.y = p_entity.getY();
	dst.w = p_entity.getCurrentFrame().w;
	dst.h = p_entity.getCurrentFrame().h;

	SDL_RenderCopy(renderer, p_entity.getTex(), &src, &dst);
}

int RendererWindow::getRefreshRate()
{
	int displayIndex = SDL_GetWindowDisplayIndex( window );

	SDL_DisplayMode mode;
	SDL_GetDisplayMode(displayIndex, 0, &mode);
	return mode.refresh_rate;
}

void RendererWindow::display()
{
	SDL_RenderPresent( renderer );
}

void RendererWindow::cleanUp()
{
	SDL_DestroyWindow( window );
}