#ifndef PIECE_H
#define PIECE_H

class Piece
//This is the header class for the Piece.cpp, this will be the super class for all the chess piece classes. 
{
    protected:
    //bool value checking whether the piece is black or not
    bool isBlack; 
    //bool value checking whether the piece is captured 
    bool isPieceCaptured;

    //current row of the piece
    int originRow;
    //current column of the piece
    int originCol;

    public:
        //Default constructor
        Piece();

        //parameterized constructor to set whether the piece base class is black or not, its captured status, and it's initial position
        Piece(bool colour, bool capturedStatus, int originRow, int originCol);

        //preforming the check of whether the piece is black or not
        bool isBlackCheck() const;

        //preforming the check of whether the piece is captured or not
        bool isCapturedCheck() const;

        //To set when the piece is captured or not
        void setCapture(bool);

        //To set whether the piece is black or not 
        void setBlack(bool);


        //using a "pure virtual function" to be later overriden by its childern classes due to the many
        //different usages of piece movement. Since it is pure it  makes this an abstract class.
        virtual bool isValidMove(int, int /*, Piece* board[8][8]*/) = 0;

        //This is another "pure virtual function" that will be overloaded by the derived classes 
        //virtual void move(int, int, Piece*, Piece* board[8][8]) = 0;
        
        //Destructor, is a virtual so that it can be overloaded by the piece class when they are destroyed so we can write out the piece has been captuared
        virtual ~Piece();
};

#endif // PIECE_H
