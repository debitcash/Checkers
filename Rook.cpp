//
// Created by zacha on 2024-11-13.
//

#include <iostream>
#include "Rook.h"

//Implementation of Rook

//Default constructor
Rook::Rook() : Piece(), originRow(0), originCol(0) {}

//Parameterized
Rook::Rook(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus), originRow(newRow),originCol(newCol) {}

//check if move is valid. Valid moves are horizontal or vertical, no limit on number of squares moved.
//captures piece if it hits it
bool Rook::isValidMove(const int destRow, const int destCol, Piece* board[8][8])
{
    bool validMove = true;

    //check if it's not a horizontal or vertical move
    if(originRow != destRow && originCol != destCol) {
        validMove = false;
    }
    //check if the destination coordinate results in a horizontal move
    else if (originRow == destRow) {

        //need to check all squares between origin and destination to ensure not running over/clipping through a piece
        for(int col = originCol + 1; col < destCol; col++) {
            //if there is a piece on the path, not a valid move
            if (board[originRow][col] != nullptr) {
                validMove = false;
                break;
            }
        }
    }
    //check if the destination coordinate results in a vertical move
    else{
        //need to check all squares between origin and destination to ensure not running over/clipping through a piece
        for(int row = originRow + 1; row < destCol; row++) {
            //if there is a piece on the path, not a valid move
            if (board[row][originCol] != nullptr) {
                validMove = false;
                break;
            }
        }
    }

    //if move is valid update the position
    if(validMove) {
        originRow = destRow;
        originCol = destCol;
    }

    return validMove;
}

//Destructor
Rook::~Rook()
{
    std::cout << "Rook has been captured" << std::endl;
}

