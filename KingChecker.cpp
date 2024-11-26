#include "KingChecker.h"
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

// holds kingChecker  class implementation logic

// default Constructor
KingChecker::KingChecker() : Piece() {};

// parameterized constructors 
KingChecker::KingChecker(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus, newRow, newCol) {}

// checks destination coordinates for valididty
bool KingChecker::isValidMove(int destRow, int destCol)
{
    bool validMove; 

    // calculating the value between the origin and destination coordinates
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));


    // making sure it's a diagonal move in any of th 4 directions
    if (value == 45 || value == 135 || value == 225 || value == 315)
    {
        // because we've already checked that's its a diagonal move we only need to check the destRow is good, no need for column check
        if((originRow + 1 == destRow)||(originRow - 1 == destRow)||(originRow + 2 == destRow)||(originRow - 2 == destRow)) {
            validMove = true;
        }
    }
    
    else 
    {
        validMove = false;
    }

    return validMove;
}

// destructor
KingChecker::~KingChecker() {
    std::cout << "King Checker has been captured." << std::endl;
}
