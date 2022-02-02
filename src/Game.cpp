#include "Game.hpp"

int wall_colision[2] = {1, 1};
float speed = 2;
float scaleTimer = 1000;
// 0-8 are color indexes 
char const *texture[9] = {"res/PNG/blue.png",
						"res/PNG/brown.png",
						"res/PNG/gray.png",
						"res/PNG/green.png",
						"res/PNG/lime.png",
						"res/PNG/orange.png",
						"res/PNG/purple.png",
						"res/PNG/red.png",
						"res/PNG/yellow.png"
};
const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
int level1[5][10] = {{0,1,2,3,4,5,6,7,8,0},
					 {2,1,2,3,4,5,6,7,8,0},
					 {1,1,6,3,7,5,6,7,8,0},
					 {0,1,8,3,3,5,6,7,8,0},
					 {0,3,6,2,7,1,5,5,2,1}
					 
};

Game::Game()
{	
	if(SDL_Init(SDL_INIT_VIDEO)> 0)
		cout<<"SDL_Init HAS FAILED. SDL_ERROR" <<SDL_GetError()<<endl;

	if(!(IMG_Init(IMG_INIT_PNG)))
		cout<<"IMG_Init HAS FAILED. SDL_ERROR" <<SDL_GetError()<<endl;

	RendererWindow window("BreakeoutSDL2",855,600);

	ballTexture = window.loadTexture("res/PNG/ball.png");
	platforma = window.loadTexture("res/PNG/platforma.png");
	live = window.loadTexture("res/PNG/live.png");
	const float tiksPerFrame = 1000/window.getRefreshRate();
	FPS = 0;
	//create vector for lives
	for(int i=0;i<61;i+=30)
	{
		lives.push_back(Entity(800 - i , 13, 24, 22, live));	
	}

	// crate vector for level
	int y = 55;
	for(int i=0; i<5; i++)
	{	
		int x = 5;
		for (int j = 0; j<10; j++)
			{	
				texture2 = window.loadTexture(texture[level1[i][j]]);
				bricks.push_back(Entity(x, y, 80, 27, texture2));
				x +=85;
			} 
			y += 32; // briks.getH() + 5;

	}
	Entity bila(400, 500, 16, 16, ballTexture);
	Entity platforma1(300, 500, 95, 20, platforma);
	spawn(bila,platforma1);
	gameRuning = true;
	
	while(gameRuning)
	{	
		int startTicks = SDL_GetTicks();
		input();
		if(lives.empty())
		{
			gameRuning = false;
		}
		if(bricks.empty())
		{
			gameRuning = false;
		}
		if(currentKeyStates[ SDL_SCANCODE_SPACE ])
		{
			wall_colision[0]= wall_colision[1] = 1;
		}
		window.clear();
		window.render(bila);
		window.render(platforma1);
		for(Entity& l_lives : lives)
		{
			window.render(l_lives);
		}
		
		for(Entity& level : bricks)
		{
			window.render(level);
		}
	
		if(bila.getY() >= 616)
			{	
				lives.erase(lives.begin());
				spawn(bila,platforma1);
			}

		if (platforma1.getX() >= (855 - platforma1.getW()))

			platforma1.setX(855 - platforma1.getW());

		else if(platforma1.getX()<=0)

			platforma1.setX(0);

		if(wall_colision[0] == 0)
		{	
			bila.setX( platforma1.getX() + (( platforma1.getW() - bila.getW() ) /2 ));
			
		}
		else
		{
			bila.setX( bila.getX() + speed* wall_colision[0]);
			bila.setY( bila.getY() - speed* wall_colision[1]);
			colisionWithWalls(bila);
			for(int  i=0 ; i < bricks.size(); i++)
			{
				if(colisionWithPlatforms(bila,bricks[i]))
					bricks.erase(bricks.begin()+i);
					

			}
			colisionWithPlatforms(bila,platforma1);
		}
		move(platforma1);
		window.display();


		float frameTicks = SDL_GetTicks()-startTicks;
		if (frameTicks < tiksPerFrame)
		{	
			FPS ++;
			SDL_Delay(tiksPerFrame-frameTicks);
		 		
		}
		
	}
	window.cleanUp();
	

}

Game::~Game()
{	
	SDL_Quit();
}

void Game::colisionWithWalls(Entity& p_entity)
{
	if(p_entity.getX() >= 839 )
		{
			wall_colision[0] = -1;
		}
		else if(p_entity.getX() <= 0)
		{
			wall_colision[0] = 1;
		}
		else if(p_entity.getY() == 50)
		{
			wall_colision[1] = -1;
		}
}

bool Game::colisionWithPlatforms(Entity& bila,Entity& platform)
{	///button
	if(bila.getY() <= platform.getY()+platform.getH() && bila.getY() >= platform.getY() && bila.getX()>=platform.getX() && bila.getX()<=platform.getX()+platform.getW() )
		{
			wall_colision[1] = -1;
			return true;
		}
	//top
	 if(bila.getY() >= platform.getY()-bila.getH() && bila.getY()<=(platform.getY()-bila.getH()) && bila.getX()>=platform.getX() && bila.getX()<=platform.getX()+platform.getW() )
		{
			wall_colision[1] = 1;
			return true;
		}
	//left
	if(bila.getX()>= platform.getX()-bila.getW() && bila.getX()<= platform.getX() && bila.getY() >= platform.getY()-bila.getH() && bila.getY() <= platform.getY()+platform.getH())
		{
			wall_colision[0] = -1;
			return true;
		}
	//right
	if(bila.getX() <= platform.getX()+platform.getW() && bila.getX()>= platform.getX()+platform.getW()-2 && bila.getY() >= platform.getY()-bila.getH() && bila.getY() <= platform.getY()+platform.getH())
		{
			wall_colision[0] = 1;
			return true;
		}
	else return false;

}

void Game::input()
 {
 	while(SDL_PollEvent(&event))
			{
				if(event.type == SDL_QUIT)
					gameRuning = false;
			}
 }

 void Game::spawn(Entity& bila, Entity& platform)
 {
 	bila.setX(400);
 	bila.setY(500);
 	platform.setX(360);
 	platform.setY(516);
 	wall_colision[0] = wall_colision[1] =  0;
 }

void Game::move(Entity& platform)
{
	if(currentKeyStates[ SDL_SCANCODE_LEFT ] || currentKeyStates[ SDL_SCANCODE_A ])
	{
		platform.setX(platform.getX() - (speed+1));
	}
	else if(currentKeyStates[ SDL_SCANCODE_RIGHT ] || currentKeyStates[SDL_SCANCODE_D ])

	{
		platform.setX(platform.getX() + (speed+1));
	}
}
