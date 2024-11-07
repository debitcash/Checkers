#include "Piece.h"
#include <iostream>

//This is the Piece.cpp class, which holds the implementation for all the code about the piece class. 

Piece::Piece(bool newColour, bool newStatus): isBlack(newColour), isPieceCaptured(newStatus){};

Piece::Piece():isBlack(false), isPieceCaptured(false){};

bool Piece::isBlackCheck() const
{
    return isBlack;
}

bool Piece::isCapturedCheck() const
{
    return isPieceCaptured;
}

void Piece::setCapture(bool newStatus)
{
    isPieceCaptured = newStatus; 
}

void Piece::setBlack(bool newColour)
{
    isBlack = newColour;
}

Piece::~Piece()
{
    std::cout << "Piece has been captured" << std::endl;
}

