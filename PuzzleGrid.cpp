#include "PuzzleGrid.h"

PuzzleGrid::PuzzleGrid()
{
}


// TODO: Ignore current piece when checking?
bool PuzzleGrid::validPieceLocation(PuzzlePiece* puzzlePiece, int x, int y)
{
	std::array<std::pair<int, int>, 4> shapeCoordinates = puzzlePiece->getShapeCoordinates();

	for (size_t i = 0; i < shapeCoordinates.size(); i++)
	{
		if (mGrid[y + shapeCoordinates[i].second][x + shapeCoordinates[i].first] == 1)
		{
			SDL_Log("Coordinate %d, %d is occupied!", x, y);
			return false;
		}
	}
	return true;
}

bool PuzzleGrid::tryAddPuzzlePieceToGrid(PuzzlePiece* puzzlePiece, int x, int y)
{
	if (!validPieceLocation(puzzlePiece, x, y))
	{
		return false;
	}
	
	std::array<std::pair<int, int>, 4> shapeCoordinates = puzzlePiece->getShapeCoordinates();

	for (size_t i = 0; i < shapeCoordinates.size(); i++)
	{
		mGrid[y + shapeCoordinates[i].second][x + shapeCoordinates[i].first] = 1;
	}

	puzzlePiece->setCoordinates(x, y);

	return true;
}

bool PuzzleGrid::tryMovePuzzlePieceToGridPosition(PuzzlePiece* puzzlePiece, int x, int y)
{
	if (!validPieceLocation(puzzlePiece, x, y))
	{
		return false;
	}
	else
	{
		// remove from original position
		std::pair<int, int> xyCoords = puzzlePiece->getCoordinates();
		std::array<std::pair<int, int>, 4> shapeCoordinates = puzzlePiece->getShapeCoordinates();
		for (size_t i = 0; i < shapeCoordinates.size(); i++)
		{
			mGrid[xyCoords.second + shapeCoordinates[i].second][xyCoords.first + shapeCoordinates[i].first] = 0;
		}

		// add to new position
		for (size_t i = 0; i < shapeCoordinates.size(); i++)
		{
			mGrid[y + shapeCoordinates[i].second][x + shapeCoordinates[i].first] = 1;
		}
	}

	return false;
}

void PuzzleGrid::render(SDL_Renderer* renderer, LTexture* texture)
{
	int gridSize = 16;
	for (size_t y = 0; y < 20; y++)
	{
		for (size_t x = 0; x < 10; x++)
		{
			if (mGrid[y][x] == 1)
			{
				texture->render(renderer, x * gridSize, y * gridSize, nullptr, gridSize, gridSize);
			}
			else
			{

			}
		}
	}
}
