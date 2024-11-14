//
// Created by zacha on 2024-11-13.
//

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

//Header file for the Rook class
class Rook : public Piece{

private:
    int originRow;
    int originCol;

public:
    //Default constructor
    Rook();

    //Parameterized constructor
    Rook(bool, bool, int, int);

    //Overloaded function to check whether it is a valid move or not.
    bool isValidMove(int, int, Piece* board[8][8]);

    //The destructor for the rook class.
    ~Rook();

};

#endif //ROOK_H
