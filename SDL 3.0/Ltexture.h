#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

class Ltexture
{
public:
	//initialize variables
	Ltexture();

	//Deallocate memory
	~Ltexture();

	bool loadFromFile(std::string path, SDL_Renderer* gRenderer);

#ifdef _SDL_TTF_H
	//Creates image from font's string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer);
#endif

	//deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimension
	int getWidth();
	int getHeight();
	SDL_Texture* getTexture();

private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//image dimensions
	int mWidth;
	int mHeight;

};

