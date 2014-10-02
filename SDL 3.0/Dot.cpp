#include "Dot.h"

Dot::Dot(int x, int y)
{
	//Initialize the offsets
	mPosX = x;
	mPosY = y;

	//Create the necessary SDL_Rects
	mCollider.r = DOT_WIDTH / 2;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;

	//Move collider relative to the circle
	shiftColliders();
}

void Dot::handleEvent(SDL_Event& e)
{
	//if a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }

	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: mVelY += DOT_VEL; break;
		case SDLK_DOWN: mVelY -= DOT_VEL; break;
		case SDLK_LEFT: mVelX += DOT_VEL; break;
		case SDLK_RIGHT: mVelX -= DOT_VEL; break;
		}
	}
}

void Dot::move(SDL_Rect& square, Circle& circle, bool (*checkCollisionCC)(Circle&, Circle&), bool (*checkCollisionCR)(Circle&, SDL_Rect&))
{
	//Move the dot left or right
	mPosX += mVelX;
	shiftColliders();

	//If the dot collided or went too far to the left or right
	if ((mPosX - mCollider.r < 0) || ((mPosX - mCollider.r + DOT_WIDTH) > SCREEN_WIDTH) || checkCollisionCR(mCollider, square) || checkCollisionCC(mCollider, circle) )
	{
		//Move back
		mPosX -= mVelX;
		shiftColliders();
	}

	//Move the dot up or down 
	mPosY += mVelY;
	shiftColliders();

	//If the dot collided or went too far up or down
	if ((mPosY - mCollider.r < 0) || ((mPosY - mCollider.r + DOT_HEIGHT) > SCREEN_HEIGHT) || checkCollisionCR(mCollider, square) || checkCollisionCC(mCollider, circle) )
	{
		mPosY -= mVelY;
		shiftColliders();
	}
}

void Dot::render(Ltexture* gDotTexture, SDL_Renderer* gRenderer)
{
	gDotTexture->render(mPosX - mCollider.r, mPosY - mCollider.r, gRenderer);
}

void Dot::shiftColliders()
{
	//Allign collidet to center of the dot
	mCollider.x = mPosX;
	mCollider.y = mPosX;
}

//Gets the colliders of the object
Circle Dot::getCollider()
{
	return mCollider;
}