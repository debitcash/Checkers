#include "Checker.h"

#include <iostream>
#include <ostream>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265

// checker Implementation class

// default constructor
Checker::Checker() : Piece() {};

// parameterized constructor. Calls parent class's constructor (piece)
Checker::Checker(bool newColour, bool newStatus, int newRow, int newCol, bool newPromotion) : Piece(newColour, newStatus, newRow, newCol), isPromoted(newPromotion) {}

bool Checker::isValidMove(int destRow, int destCol) {

    bool validMove;

    // calculating the angle between the origin and destination coordinate
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));

    // making sure it's a diagonal move
    if (value == 45 || value == 135 ) {
        
        // standard Move, no capture
        // because we've already checked that's its a diagonal move we only need to check the destRow is good, not the column also
        if((originRow + 1 == destRow)||(originRow + 2 == destRow))
        {
            validMove = true;
        }
    }
    
    else 
    {
        validMove = false;
    }

    return validMove;
}

Checker::~Checker() {
    std::cout << "Checker has been captured." << std::endl;
}

// promote checker if reached the opposite side of the board
bool Checker::promotion()
{
    if(originRow == 7)
    {
        return true; 
    }
    
    return false; 
}

// check if its a kingChecker
bool Checker::getPromotionCheck()
{
    return isPromoted;
}
