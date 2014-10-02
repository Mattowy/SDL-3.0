#include "Ltexture.h"

//Button constants
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
	BUTTON_SPRITE_MOUSE_OUT = 0,
	BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
	BUTTON_SPRITE_MOUSE_DOWN = 2,
	BUTTON_SPRITE_MOUSE_UP = 3,
	BUTTON_SPRITE_TOTAL = 4

};

class LButton
{
public:
	LButton();
	
	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	void handleEvent(SDL_Event* e);

	//showes button sprite
	void render(Ltexture* gButtonSheetTexture, SDL_Renderer* gRenderer, SDL_Rect* gSpriteClips);

	LButtonSprite getCurr();

private:
	//Top left position
	SDL_Point mPosition;

	//Current used global sprite
	LButtonSprite mCurrentSprite;
};

