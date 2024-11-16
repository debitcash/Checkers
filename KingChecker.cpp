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


    //Calculating the value between the origin and destitnation coordinates. 
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));


    //So because when you draw out the degrees visually and 90 and 270 are "opposites of each other", so I think by 
    //calculating 225 
    if (value == 45 || value == 135 || value == 225 || value == 315)
    {

    if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))){
        validMove = true;
    }
    //Moving down just by one
    else if ( (originRow - 1 == destRow) && ((originCol - 1 == destCol) || (originCol + 1 ==destCol)))
    {
        validMove = true;
    }
     else if((originRow + 2 == destRow) && (originCol + 2 == destCol) && () || (originCol - 2 == destCol) ){

           validMove = true; 
        }



    }


}