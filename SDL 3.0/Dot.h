#include "LTimer.h"

//Circle structure
struct Circle
{
	int x, y;
	int r;
};

class Dot
{
public:
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;

	//Initializes the variables
	Dot(int x, int y);

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);
	
	//moves the dot
	void move(SDL_Rect& square, Circle& circle, bool(*checkCollisionCC)(Circle&, Circle&), bool(*checkCollisionCR)(Circle&, SDL_Rect&));

	//Shows the dot on the screen
	void render(Ltexture* gDotTexture, SDL_Renderer* gRenderer);

	Circle getCollider();

private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Dot's collision boxes
	Circle mCollider;

	//Moves the collision boxes relative to the dot's offset
	void shiftColliders();
};

