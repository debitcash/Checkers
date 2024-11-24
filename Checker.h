

#ifndef CHECKER_H
#define CHECKER_H

#include "Piece.h"

class Checker : public Piece {

private:
bool isPromoted;

public:
    //Default constructor
    Checker();
    //Parameterized constructor
    Checker(bool colour, bool capturedStatus, int originRow, int orignCol, bool promotionStatus);

    //Overloaded function to check whether it is a valid move or not.
    bool isValidMove(int destRow, int destCol /*, Piece* board[8][8]*/);


    bool promotion();

    bool getPromotionCheck();

    //The destructor for the checker class.
    ~Checker();
};

#endif //CHECKER_H

