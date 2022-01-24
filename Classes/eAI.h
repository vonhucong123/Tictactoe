#pragma once

#include "cocos2d.h"
#include <vector>
#include <array>

class AI
{
public:
    AI(int playerPiece);

    void PlacePiece();
    int getXOut();
    int getYOut();
    void setMatrixChecked(int matrix[3][3]);
    void checkSection(int x1, int y1, int x2, int y2, int X, int Y);
private:
    void CheckIfPieceIsEmpty(int X, int Y, int &xOut, int &yOut);

    int aiPiece;
    int playerPiece;
    int xOut, yOut;
    int matrixChecked[3][3];

    std::vector<std::array<int, 6>> checkMatchVector;

};