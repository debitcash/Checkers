

#include "Checker.h"

#include <iostream>
#include <ostream>

//Checker Implementation class

//Default constructor
Checker::Checker() : Piece(){};

//Parameterized constructor. Calls parent class's constructor (piece)
Checker::Checker(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus, newRow, newCol) {}


bool Checker::isValidMove(int destRow, int destCol, Piece* board[8][8]) {

    bool validMove;

    //requested destination must not have a piece there already
    if (board[destRow][destCol] != nullptr) {
        validMove = false;
    }
    //Standard single space move
    else if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))){
        validMove = true;
    }
    //Capture move
    




    if(validMove) {
        originRow = destRow;
        originCol = destCol;
    }
    return validMove;
}


Checker::~Checker() {
    std::cout << "Checker has been captured." << std::endl;
}




