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

//*************************************************************************************


//*************************************************************************************
bool Checker::isValidMove(int destRow, int destCol /*, Piece* board[8][8]*/) {

    bool validMove;

    //requested destination must not have a piece there already
    //requested destination must not have a piece there already.
    /*if (board[destRow][destCol] != nullptr) {
        validMove = false;
        return false;
    }*/
    //Standard single space move
    /*if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))){
        validMove = true;
    }*/
    //Capture move
    
    //std::cout <<originRow <<originCol << " " << destRow<<destRow;
    //calculating the angle between the origin and destination coordinate
    int value = std::abs(std::round(atan2 (destRow - originRow,destCol - originCol) * 180 / PI));

    //Making sure it's a diagonal move
    if (value == 45 || value == 135 ) {
        
        //Standard Move, no capture
        //Because we've already checked that's its a diagonal move we only need to check the destRow is good, not the column also
        if((originRow + 1 == destRow)||(originRow + 2 == destRow)) /*&& ((originCol + 1 == destCol) || (originCol - 1 == destCol))*/ {
            validMove = true;
        }

        /*else if((originRow + 2 == destRow) /*&& (originCol + 2 == destCol) || (originCol - 2 == destCol)#1# ){
            //An interesting math concept is that the average of the two points are the midpoint
            //Because you are getting the "middle" of x and y, so we should be able to use the midpoint.
            //And with the midpoint, we can see if there is a checker inbetween it so that can modify it. 

            /*int midRow = ((destRow + originRow)/2);
            int midCol = ((destCol + originCol)/2);

            if(board[midRow][midCol] != nullptr)
            {
                validMove = true; 
            }
            else
            {
                validMove = false; 
            }#1#
           
           validMove = true; 
        }*/
    }
    else {
        validMove = false;
    }

    //if move is successful, update position of checker
    /*if(validMove) {
        originRow = destRow;
        originCol = destCol;
    }*/

    return validMove;
}

Checker::~Checker() {
    std::cout << "Checker has been captured." << std::endl;
}
