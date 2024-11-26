// checker header file
#ifndef CHECKER_H
#define CHECKER_H

#include "Piece.h"

// define class checker
class Checker : public Piece {

private:
bool isPromoted;

public:
    // default constructor
    Checker();
    
    // parameterized constructor
    Checker(bool colour, bool capturedStatus, int originRow, int orignCol, bool promotionStatus);

    // overloaded function to check whether it is a valid move or not.
    bool isValidMove(int destRow, int destCol);

    bool promotion();

    bool getPromotionCheck();

    // the destructor for the checker class.
    ~Checker();
};

#endif //CHECKER_H

