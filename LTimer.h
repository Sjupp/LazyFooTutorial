#pragma once
#include <SDL3/SDL_timer.h>

class LTimer
{
public:
	LTimer();

	void start();
	void stop();
	void pause();
	void unpause();

	Uint64 getTicksNS();

	bool isStarted();
	bool isPaused();

private:
	Uint64 mStartTicks;
	Uint64 mPausedTicks;

	bool mPaused;
	bool mStarted;
};