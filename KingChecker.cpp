#include "KingChecker.h"
#include <iostream>
#include <ostream>
#include <stdio.h>
#include <math.h>

#define PI 3.14159265


//Default Constructor
KingChecker::KingChecker() : Piece() {};

//Parameterized constructors 
KingChecker::KingChecker(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus, newRow, newCol) {}

bool KingChecker::isValidMove(int destRow, int destCol)
{
    bool validMove; 

    //Keeping the orginally moving up rule.


    //Calculating the value between the origin and destination coordinates.
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));


    //So because when you draw out the degrees visually and 90 and 270 are "opposites of each other", so I think by 
    //calculating 225 
    if (value == 45 || value == 135 || value == 225 || value == 315)
    {
        //Because we've already checked that's its a diagonal move we only need to check the destRow is good, not the col also
        if((originRow + 1 == destRow)||(originRow - 1 == destRow)||(originRow + 2 == destRow)||(originRow - 2 == destRow)) {
            validMove = true;
        }

        /*if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))){
            validMove = true;
        }
        //Moving down just by one
        else if ( (originRow - 1 == destRow) && ((originCol - 1 == destCol) || (originCol + 1 ==destCol)))
        {
            validMove = true;
        }
         else if((originRow + 2 == destRow) && (originCol + 2 == destCol) && () || (originCol - 2 == destCol) ){

               validMove = true;
         }*/

    }
    else {
        validMove = false;
    }

    return validMove;
}

KingChecker::~KingChecker() {
    std::cout << "King Checker has been captured." << std::endl;
}