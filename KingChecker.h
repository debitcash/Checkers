#ifndef KINGCHECKER_H
#define KINGCHECKER_H

#include "Piece.h"

// KingChecker class specifies details for king pieces
class KingChecker : public Piece{
public:
    // constructor
    KingChecker();
    
    // parametersized constructor
    KingChecker(bool colour, bool capturedStatus, int originRow, int originCol);

    // check if coordinates are valid
    bool isValidMove(int destRow, int destCol);

    // destructor
    ~KingChecker();
};

#endif
