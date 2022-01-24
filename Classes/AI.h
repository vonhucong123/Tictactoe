#pragma once

#include "cocos2d.h"
#include <vector>
#include <array>

class AI
{
public:
    AI(int playerPiece);

    void PlacePiece(int(*gridArray)[3][3]);
    int getYOut();
    int getXOut();

private:
    void CheckSection(int x1, int y1, int x2, int y2, int X, int Y, int pieceToCheck, int(*gridArray)[3][3]);
    void CheckIfPieceIsEmpty(int X, int Y, int(*gridArray)[3][3]);

    int aiPiece;
    int playerPiece;
    int xOut;
    int yOut;

    std::vector<std::array<int, 6>> checkMatchVector;

};