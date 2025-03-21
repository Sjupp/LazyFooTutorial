#include "LTimer.h"

LTimer::LTimer() :
	mStartTicks{ 0 },
	mPausedTicks{ 0 },
	mStarted{ false },
	mPaused{ false	}
{
}

void LTimer::start()
{
	mStarted = true;
	mPaused = false;
	
	mStartTicks = SDL_GetTicksNS();
	mPausedTicks = 0;
}

void LTimer::stop()
{
	mStarted = false;
	mPaused = false;

	mStartTicks = 0;
	mPausedTicks = 0;
}

void LTimer::pause()
{
	if (mStarted && !mPaused)
	{
		mPaused = true;

		mPausedTicks = SDL_GetTicksNS() - mStartTicks;
		mStartTicks = 0;
	}
}

void LTimer::unpause()
{
	if (mStarted && mPaused)
	{
		mPaused = false;

		mStartTicks = SDL_GetTicksNS() - mPaused; 

		mPausedTicks = 0;
	}
}

Uint64 LTimer::getTicksNS()
{
	Uint64 time = 0;

	if (mStarted)
	{
		if (mPaused)
		{
			time = mPausedTicks;
		}
		else
		{
			time = SDL_GetTicksNS() - mStartTicks;
		}
	}

	return time;
}

bool LTimer::isStarted()
{
	return mStarted;
}
bool LTimer::isPaused()
{
	return mPaused;
}