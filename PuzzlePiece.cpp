#include "PuzzlePiece.h"
#include <iostream>
#include <sstream>

PuzzlePiece::PuzzlePiece()
{
}

void PuzzlePiece::rotateClockwise()
{
    int indexSize = 3;
    if (mFourPiece)
    {
        indexSize = 4;
    }

    int temp[4][4];

    std::stringstream debugText;

    // Rotate the matrix by 90 degrees clockwise
    for (int i = 0; i < indexSize; i++) {
        for (int j = 0; j < indexSize; j++) {
            temp[j][(indexSize - 1) - i] = mShape[i][j];
        }
    }

    // Copy the rotated matrix back to the original matrix
    for (int i = 0; i < indexSize; i++) {
        for (int j = 0; j < indexSize; j++) {
            mShape[i][j] = temp[i][j];
            debugText << mShape[i][j] << " ";
        }
        debugText << "\n";
    }
    debugText << "\n";
    SDL_Log(debugText.str().c_str());
}

std::pair<int, int> PuzzlePiece::getCoordinates()
{
    return std::pair<int, int> { xGridPosition, yGridPosition };
}

void PuzzlePiece::setCoordinates(int x, int y)
{
    xGridPosition = x;
    yGridPosition = y;
}

std::array<std::pair<int, int>, 4> PuzzlePiece::getShapeCoordinates()
{
    std::array<std::pair<int, int>, 4> coordinates{};
    int count = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (mShape[i][j] == 1) {
                coordinates[count++] = { i, j }; // Save coordinate
                if (count == 4) break; // Stop once we find 4
            }
        }
        if (count == 4) break; // Stop early if all 4 are found
    }

    return coordinates;
}
