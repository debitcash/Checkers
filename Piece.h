#ifndef PIECE_H
#define PIECE_H

// Piece class stores general piece information
class Piece {
protected:
    // bool value checking whether the piece is black or not
    bool isBlack; 
    // bool value checking whether the piece is captured 
    bool isPieceCaptured;

    // current row of the piece
    int originRow;
    // current column of the piece
    int originCol;

public:
    // default constructor
    Piece();

    // parameterized constructor to set whether the piece base class is black or not, its captured status, and it's initial position
    Piece(bool colour, bool capturedStatus, int originRow, int originCol);

    // peforming the check of whether the piece is black or not
    bool isBlackCheck() const;

    // peforming the check of whether the piece is captured or not
    bool isCapturedCheck() const;

    // set when the piece is captured or not
    void setCapture(bool);

    // set whether the piece is black or not 
    void setBlack(bool);

    // using a "pure virtual function" to be later overriden by its childern classes due to the many
    // different usages of piece movement. Since it is pure it  makes this an abstract class.
    virtual bool isValidMove(int, int) = 0;
    
    void setOriginCol(int);
    void setOriginRow(int);
    
    // destructor, is virtual so that it can be overloaded by the piece class when they are destroyed so we can write out that the piece has been captuared
    virtual ~Piece();
};

#endif // PIECE_H
