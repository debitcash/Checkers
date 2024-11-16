#include "Checker.h"

#include <iostream>
#include <ostream>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

//Checker Implementation class

//Default constructor
Checker::Checker() : Piece(){};

//Parameterized constructor. Calls parent class's constructor (piece)
Checker::Checker(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus, newRow, newCol) {}


bool Checker::isValidMove(int destRow, int destCol, Piece* board[8][8]) {

    bool validMove;

    //requested destination must not have a piece there already.
    if (board[destRow][destCol] != nullptr) {
        return false;
    }

    //calculating the angle between the origin and destination coordinate
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));

    //Making sure it's a diagonal move
    if(value == 45 || value == 135 ) {
        //Standard Move, no capture
        if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))) {
            validMove = true;
        }
        //check for single capture move
        //needs to make sure opposite colour piece is directly in front of piece

        //test if piece is there first
        //then test if the piece isBlack() or !isBlack()
        //if the right color then validMove
        else if() {


        }
    }
    else {
        validMove = false;
    }

    //if move is successful, update position of checker
    if(validMove) {
        originRow = destRow;
        originCol = destCol;
    }

    return validMove;
}


Checker::~Checker() {
    std::cout << "Checker has been captured." << std::endl;
}






