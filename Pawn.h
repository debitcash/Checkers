#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"
class Pawn : public Piece
//This is the header file for the Pawn class.
{
    private: 
    int originRow;
    int originCol;

    public:
    //Overloaded function to check whether it is a valid move or not.
    bool isValidMove(int, int, Piece* board[8][8]);
    //Default constructor
    Pawn();
    //Parameterized constructor
    Pawn(bool, bool, int, int);
    //Overloaded function for the movement of the piece.
    //void move(int, int, Piece*, Piece* board[8][8]);
    
    //The destructor for the pawn class. 
    ~Pawn();
};

#endif // PAWN_H