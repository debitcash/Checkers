
#ifndef CHECKER_H
#define CHECKER_H

#include "Piece.h"

class Checker : public Piece {

public:
    //Default constructor
    Checker();
    //Parameterized constructor
    Checker(bool colour, bool capturedStatus, int originRow, int orignCol);

    //Overloaded function to check whether it is a valid move or not.
    bool isValidMove(int destRow, int destCol /*, Piece* board[8][8]*/);

    //The destructor for the checker class.
    ~Checker();
};

#endif //CHECKER_H
