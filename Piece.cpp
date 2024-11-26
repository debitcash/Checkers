#include "Piece.h"
#include <iostream>

// class, which holds the implementation for all the code about the piece class. 

// parameterized constructor
Piece::Piece(bool newColour, bool newStatus, int row, int col): isBlack(newColour), isPieceCaptured(newStatus), originRow(row), originCol(col){};

Piece::Piece():isBlack(false), isPieceCaptured(false), originRow(-1), originCol(-1){};

// check if the piece is black color
bool Piece::isBlackCheck() const
{
    return isBlack;
}

// check if piece is captured
bool Piece::isCapturedCheck() const
{
    return isPieceCaptured;
}

// change captured status
void Piece::setCapture(bool newStatus)
{
    isPieceCaptured = newStatus; 
}

// set new color for a piece
void Piece::setBlack(bool newColour)
{
    isBlack = newColour;
}

// setter to update origin column
void Piece::setOriginCol(int newOriginCol) {
    originCol = newOriginCol;
}

// setter to update origin row
void Piece::setOriginRow(int newOriginRow) {
    originRow = newOriginRow;
}

// destructor, for when a piece is captured, was primarily used for debugging
Piece::~Piece()
{
    //std::cout << "Piece has been captured" << std::endl;
}

