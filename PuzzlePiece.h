#pragma once
#include <SDL3/SDL_render.h>
#include "LTexture.h"
#include <array>

class PuzzlePiece
{
public:
	static constexpr int kBoxCount{ 4 };

	PuzzlePiece();

	void rotateClockwise();
	std::pair<int, int> getCoordinates();
	void setCoordinates(int x, int y);
	std::array<std::pair<int, int>, 4> getShapeCoordinates();

	// split (land?)
private:
	int mShape[4][4]
	{
		{ 0, 0, 0 ,0 },
		{ 0, 1, 1 ,0 },
		{ 1, 1, 0 ,0 },
		{ 0, 0, 0 ,0 }
	};

	bool mFourPiece = false;
	int xGridPosition = 0;
	int yGridPosition = 0;
};

// TOOD: Squiggly pieces, like straight pieces, only need 2 rotation, not 4 