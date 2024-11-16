#ifndef CHECKER_H
#define CHECKER_H

#include "Piece.h"

class KingChecker : public Piece
{

    KingChecker();

    KingChecker(bool colour, bool captuaredStatus, int originRow, int originCol);

    bool isValidMove(int destRow, int destCol);

    ~KingChecker();

}