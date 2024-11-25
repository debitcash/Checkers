#ifndef KINGCHECKER_H
#define KINGCHECKER_H

#include "Piece.h"

class KingChecker : public Piece
{

    public:
    
    KingChecker();

    KingChecker(bool colour, bool capturedStatus, int originRow, int originCol);

    bool isValidMove(int destRow, int destCol);

    ~KingChecker();

};

#endif