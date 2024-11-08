#include "Pawn.h"
#include "Piece.cpp"
#include <iostream>
//This is the pawn implementation class. 


    //Old implementation of the constructors

       /* Pawn(bool newIsBlack): isBlack(newIsBlack){}
        Pawn(bool newIsBlack, int newRow, int newCol) {
            isBlack = newIsBlack;
            originRow = newRow;
            originCol = newCol;
        }*/
        
        //It will already inherit this from the piece class so it is no longer needed here.
        /*bool isBlackCheck()
        {
            return isBlack;
        }*/

       //New Constructors

       //Default 
       Pawn::Pawn() : Piece(), originRow(0), originCol(0) {}

       //Parameterized 
       Pawn::Pawn(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus), originRow(newRow),originCol(newCol) {}




        //check if move is valid(move forward only, can move in diagonal if capturing opposing color pieces)
           bool Pawn::isValidMove(int destRow, int destCol, Piece* board[8][8]) {
            //single space move
            if(originRow + 1 == destRow && originCol == destCol) {
                return true;
            }
            
            
            
            //double space move (only valid from starting position)
            if(originRow == 2){ //if the pawn is in the starting row
                if(originRow + 2 == destRow && originCol == destCol) {
                    return true;
                }
            }

            //There is checking whether there is a piece or not. So if it is a nullptr(no piece), then you will not be able make the move. 
            if(board[destRow][destCol] != nullptr)
            {
	            //diagonal capture move
	            if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol))) {
	                return true;
	            }

            }
            
            bool oppOnLeft = false;
            bool oppOnRight = false;
            
            // diagonal capture move check, first check if it the direction is actual diagona \ or /, then check if there is an opposing color piece located on there
            if (destCol == originCol - 1)
            	oppOnLeft = ((destRow == originRow + 1 && destCol == originCol - 1) && (board[originRow + 1][originCol - 1] -> isBlackCheck() != this->isBlackCheck())) ? true : false;
            else if (destCol == originCol + 1)
				oppOnRight = ((destRow == originRow + 1 && destCol == originCol + 1) && (board[originRow + 1][originCol + 1] -> isBlackCheck() != this->isBlackCheck())) ? true : false;
            
			if (oppOnLeft || oppOnRight)
            	return true;
            
            
            return false;
        }

        void Pawn::move(int destRow, int destCol, Piece* piece, Piece* board[8][8]) {

            //Capture logic
            if(board[destRow][destCol] != nullptr)
            {
                //deleting the old piece, it should call the destructor so the destructor will call it being "captuared"
                delete board[destRow][destCol];
                //assign the piece to the new location 
                board[destRow][destCol] = board[originRow][originCol];

                board[originRow][originCol];
            }
            else
            {
            // assign the piece to new location and empty the previous location
            board[destRow][destCol] = board[originRow][originCol];
            // delete the object here?
            board[originRow][originCol] = nullptr;

            originRow = destRow;
            originCol = destCol;

            }     
            
            
           }

        //Pawn class's destructor
        Pawn::~Pawn()
        {
            std::cout << "Pawn has been captured" << std::endl;
        }