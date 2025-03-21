#pragma once
#include <SDL3/SDL_render.h>
#include "LTexture.h"

class PuzzlePiece
{
public:
	static constexpr int kBoxCount{ 4 };

	PuzzlePiece();

	void rotateClockwise();
	// split (land?)
	// getShape / getOccupyingGridSlots
private:
	int mShape[4][4]
	{
		{ 0, 0, 0 ,0 },
		{ 0, 1, 1 ,0 },
		{ 1, 1, 0 ,0 },
		{ 0, 0, 0 ,0 }
	};

	bool fourPiece = false;
};

// TOOD: Squiggly pieces, like straight pieces, only need 2 rotation, not 4