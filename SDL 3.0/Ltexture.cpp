#include "Ltexture.h"


Ltexture::Ltexture() : mTexture(NULL), mWidth(0), mHeight(0) {}


Ltexture::~Ltexture()
{
	free();
}

bool Ltexture::loadFromFile(std::string path, SDL_Renderer* gRenderer ){
	//deallocate the texture in case there's one already loaded
	free();

	SDL_Texture* newTexture = NULL;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL){
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else{
		//color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));
		//color cyan 0,255,255

		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL){
			printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		else{
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
		
	}
	//return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void Ltexture::free(){
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Ltexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	
	//set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

void Ltexture::setColor(Uint8 red, Uint8 green, Uint8 blue){
	//Modulate texture
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

int Ltexture::getWidth(){
	return mWidth;
}

int Ltexture::getHeight(){
	return mHeight;
}

void Ltexture::setBlendMode(SDL_BlendMode blending){
	//set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Ltexture::setAlpha(Uint8 alpha){
	//Modulate textures' alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

SDL_Texture* Ltexture::getTexture(){
	return mTexture;
}

#ifdef _SDL_TTF_H
bool Ltexture::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* gFont, SDL_Renderer* gRenderer){
	//get rid of preexisting texture;
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface == NULL){
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL){
			printf("Unable to create texture from rendered surface! SDL Error: %s\n", SDL_GetError());
		}
		else{
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}
	}

	return mTexture != NULL;
}
#endif