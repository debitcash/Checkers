#ifndef KINGCHECKER_H
#define KINGCHECKER_H

#include "Piece.h"

class KingChecker : public Piece
{

    KingChecker();

    KingChecker(bool colour, bool capturedStatus, int originRow, int originCol);

    bool isValidMove(int destRow, int destCol);

    ~KingChecker();

};

#endif