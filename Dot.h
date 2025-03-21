#pragma once
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_render.h>
#include "LTexture.h"

class Dot
{
public:
	static constexpr int kDotVel = 10;

	Dot(int texWidth, int texHeight);

	void handleEvent(SDL_Event& e);
	void move();
	void render(SDL_Renderer* renderer, LTexture* texture);

private:
	int mPosX, mPosY;
	int mVelX, mVelY;
	int mTextureWidth, mTextureHeight;
};
