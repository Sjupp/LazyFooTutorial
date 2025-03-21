#include "Dot.h"
#include "constants.h"

Dot::Dot(int texWidth, int texHeight) : 
	mPosX{ 0 },
	mPosY{ 0 },
	mVelX{ 0 },
	mVelY{ 0 },
	mTextureWidth { texWidth },
	mTextureHeight { texHeight }
{
}

void Dot::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0)
	{
		switch (e.key.key)
		{
		case SDLK_UP: mVelY -= kDotVel; break;
		case SDLK_DOWN: mVelY += kDotVel; break;
		case SDLK_LEFT: mVelX -= kDotVel; break;
		case SDLK_RIGHT: mVelX += kDotVel; break;
		}
	}

	if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0)
	{
		switch (e.key.key)
		{
		case SDLK_UP: mVelY += kDotVel; break;
		case SDLK_DOWN: mVelY -= kDotVel; break;
		case SDLK_LEFT: mVelX += kDotVel; break;
		case SDLK_RIGHT: mVelX -= kDotVel; break;
		}
	}
}

void Dot::move()
{
	mPosX += mVelX;
	if ((mPosX < 0) || (mPosX + mTextureWidth > ScreenDimensions::kScreenWidth))
	{
		mPosX -= mVelX;
	}

	mPosY += mVelY;
	if ((mPosY < 0) || (mPosY + mTextureHeight > ScreenDimensions::kScreenHeight))
	{
		mPosY -= mVelY;
	}
}

void Dot::render(SDL_Renderer* renderer, LTexture* texture)
{
	texture->render(renderer, mPosX, mPosY);
}