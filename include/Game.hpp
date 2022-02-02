#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>
using namespace std;


#include "RenderWindow.hpp"
#include "utils.hpp"
class Game
{
public:
	Game();
	void input();
	void colisionWithWalls(Entity& p_entity);
	bool colisionWithPlatforms(Entity& bila,Entity& platform);
	void spawn(Entity& bila, Entity& platform);
	void move(Entity& platform);
   ~Game();

private:
	int FPS;
	float frameDelay = 1000/60;
	float frameTime;
	float frameStart;
	vector<Entity> lives,bricks;
	SDL_Texture* ballTexture, *texture2, *platforma, *live;
	SDL_Event event;
	bool gameRuning , gameLoad;

};