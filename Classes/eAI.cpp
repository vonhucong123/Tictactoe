#include "AI.h"
#include "Definitions.h"

#include <iostream>

using namespace std;

AI::AI(int playerPiece)
{
    this->playerPiece = playerPiece;

    if (O_PIECE == playerPiece)
    {
        aiPiece = X_PIECE;
    }
    else
    {
        aiPiece = O_PIECE;
    }

    checkMatchVector.push_back({ 0, 2, 1, 2, 2, 2 });
    checkMatchVector.push_back({ 0, 2, 0, 1, 0, 0 });
    checkMatchVector.push_back({ 0, 2, 1, 1, 2, 0 });
    checkMatchVector.push_back({ 2, 2, 1, 2, 0, 2 });
    checkMatchVector.push_back({ 2, 2, 2, 1, 2, 0 });
    checkMatchVector.push_back({ 2, 2, 1, 1, 0, 0 });
    checkMatchVector.push_back({ 0, 0, 0, 1, 0, 2 });
    checkMatchVector.push_back({ 0, 0, 1, 0, 2, 0 });
    checkMatchVector.push_back({ 0, 0, 1, 1, 2, 2 });
    checkMatchVector.push_back({ 2, 0, 2, 1, 2, 2 });
    checkMatchVector.push_back({ 2, 0, 1, 0, 0, 0 });
    checkMatchVector.push_back({ 2, 0, 1, 1, 0, 2 });
    checkMatchVector.push_back({ 0, 1, 1, 1, 2, 1 });
    checkMatchVector.push_back({ 1, 2, 1, 1, 1, 0 });
    checkMatchVector.push_back({ 2, 1, 1, 1, 0, 1 });
    checkMatchVector.push_back({ 1, 0, 1, 1, 1, 2 });
    checkMatchVector.push_back({ 0, 1, 2, 1, 1, 1 });
    checkMatchVector.push_back({ 1, 2, 1, 0, 1, 1 });
    checkMatchVector.push_back({ 0, 2, 2, 0, 1, 1 });
    checkMatchVector.push_back({ 2, 2, 0, 0, 1, 1 });
    checkMatchVector.push_back({ 0, 2, 2, 2, 1, 2 });
    checkMatchVector.push_back({ 0, 0, 2, 0, 1, 0 });
    checkMatchVector.push_back({ 0, 2, 0, 0, 0, 1 });
    checkMatchVector.push_back({ 2, 2, 2, 0, 2, 1 });
}

void AI::PlacePiece()
{
    try
    {
        // check if center is empty
        CheckIfPieceIsEmpty(1, 1, xOut, yOut);

        // check if a corner is empty
        CheckIfPieceIsEmpty(0, 2, xOut, yOut);
        CheckIfPieceIsEmpty(2, 2, xOut, yOut);
        CheckIfPieceIsEmpty(0, 0, xOut, yOut);
        CheckIfPieceIsEmpty(2, 0, xOut, yOut);

        // check for any other empty piece
        CheckIfPieceIsEmpty(1, 2, xOut, yOut);
        CheckIfPieceIsEmpty(0, 1, xOut, yOut);
        CheckIfPieceIsEmpty(2, 1, xOut, yOut);
        CheckIfPieceIsEmpty(1, 0, xOut, yOut);
    }
    catch (int error)
    {

    }
}

int AI::getXOut()
{
    return xOut;
}

int AI::getYOut()
{
    return yOut;
}

void AI::setMatrixChecked(int matrix[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrixChecked[i][j] = matrix[i][j];
        }
    }
}

void AI::CheckIfPieceIsEmpty(int X, int Y, int &xOut, int &yOut)
{
    // check if
    if (0 == matrixChecked[X][Y])
    {
        //matrixChecked[X][Y] = 2;
        xOut = X;
        yOut = Y;
        throw - 2;
    }
}