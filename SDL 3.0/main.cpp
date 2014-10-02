#include "Dot.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool checkCollision(Circle* a, Circle* b);
bool checkCollision(Circle* a, SDL_Rect* b);

double distanceSquared(int x1, int y1, int x2, int y2);

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
//TTF_Font* gFont = NULL;

Ltexture gDotTexture;

Ltexture yShallNotPass;

bool init(){

	bool success = true;
	//set texture filtering to linear
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Failed to initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning! Linear texture filtering not enabled!\n");
		}
		gWindow = SDL_CreateWindow("Super Okno!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL){
				printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError);
				success = false;
			}
			else
			{
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)){
					printf("SDL_image could not be initialized! SDL Error %s\n", IMG_GetError());
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

				//if (TTF_Init() == -1){
				//	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
				//	success = false;
				//}

			}
		}
	}
	return success;
}
//Initialize SDL_mixer
bool loadMedia()
{
	bool success = true;
	/*gFont = TTF_OpenFont("C:/Users/Mattowy/Desktop/Studia/Projects/Nauka SDL/SDL 3.0/Debug/fonts/lazy.ttf", 28);
	if (gFont == NULL){
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}*/

	if (!gDotTexture.loadFromFile("C:/Users/Mattowy/Desktop/Studia/Projects/Nauka SDL/SDL 3.0/Debug/images/dot.bmp", gRenderer))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}
	return success;	
}

void close(){

	gDotTexture.free();

	//Free global font
	//TTF_CloseFont(gFont);
	//gFont = NULL;

	//Destroy window;
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	//TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision(Circle& a, Circle& b)
{
	//Calculate total radius squared
	int totalRadiusSquared = a.r + b.r;
	//totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;

	//If the distance between the centers of the circles is less than the sum of their radii
	if (sqrt(distanceSquared(a.x, a.y, b.x, b.y)) < (totalRadiusSquared))
	{
		//The circles have collided
		return true;
	}

	//If not
	return false;
}

bool checkCollision(Circle& a, SDL_Rect& b)
{
	//rectangle's points of width
	int x1, x2;
	//rectangle's points of height
	int y1, y2;
	x1 = b.x;
	x2 = b.x + b.w;
	y1 = b.y;
	y2 = b.y + b.h; 

	//If the objects is in a rectangle -  (x1,x2) and (y1,y2)
	if ((a.x >= x1) && (a.x <= x2) && (a.y >= y1) && (a.y <= y2))
		return true;
	else
		return false; 
}

double distanceSquared(int x1, int y1, int x2, int y2)
{
	int deltaX = x2 - x1;
	int deltaY = y2 - y1;
	return deltaX*deltaX + deltaY*deltaY;
}

int main(int argc, char* args[])
{
	//Start up SDL and create window

	if (!init()){
		printf("Failed to initialize! \n");
	}
	else{
		//Load media
		if (!loadMedia()){
			printf("Failed to load media! \n");
		}
		else

		{
			//main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Dot that will be movind around on the screen
			Dot dot(Dot::DOT_WIDTH / 2, Dot::DOT_HEIGHT / 2);

			//The dot that will be collided against
			Dot otherDot(SCREEN_WIDTH *3 / 4, SCREEN_HEIGHT / 4);

			//Wall definition
			SDL_Rect wall = { 300, 40, 40, 400 };

			while (!quit)
			{
				while (SDL_PollEvent(&e) != 0)
				{
					//User request quit
					if (e.type == SDL_QUIT){
						quit = true;
					}

					if (e.type == SDL_KEYDOWN)
					{
						if (e.key.keysym.sym == SDLK_ESCAPE)
							quit = true;
					}
					dot.handleEvent(e);
				}
				//move dot and check collision
				dot.move(wall, otherDot.getCollider(), &checkCollision, &checkCollision);

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(gRenderer);

				//Draw wall
				SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xFF);
				SDL_RenderDrawRect(gRenderer, &wall);

				//Render objects
				otherDot.render(&gDotTexture, gRenderer);
				dot.render(&gDotTexture, gRenderer);
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
		}
	}
	close();
	return 0;
}