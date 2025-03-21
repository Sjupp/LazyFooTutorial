#include "PuzzlePiece.h"
#include <iostream>
#include <sstream>

PuzzlePiece::PuzzlePiece()
{
}

void PuzzlePiece::rotateClockwise()
{
    int indexSize = 3;
    if (fourPiece)
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