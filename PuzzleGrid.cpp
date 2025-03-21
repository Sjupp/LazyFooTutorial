#include "PuzzleGrid.h"

PuzzleGrid::PuzzleGrid()
{
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
