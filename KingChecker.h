#ifndef KINGCHECKER_H
#define KINGCHECKER_H

#include "Piece.h"

// holds kingChecker class declarations

class KingChecker : public Piece
{

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
