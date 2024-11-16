#include "Pawn.h"
#include <iostream>
//This is the pawn implementation class. 

       //New Constructors

       //Default 
       Pawn::Pawn() : Piece(), originRow(0), originCol(0) {}

       //Parameterized 
       Pawn::Pawn(bool newColour, bool newStatus, int newRow, int newCol) : Piece(newColour, newStatus), originRow(newRow),originCol(newCol) {}

        //check if move is valid(move forward only, can move in diagonal if capturing opposing color pieces)
       bool Pawn::isValidMove(int destRow, int destCol, Piece* board[8][8]) 
	   {	
	   		// check if there is no piece on the square where we are moving forward to, if there is a piece, we can only diagonally move to it
	   		if(board[destRow][destCol] == nullptr)
	   		{
	            //single space move
	            if(originRow + 1 == destRow && originCol == destCol){
	            	originRow = destRow;
	            	originCol = destCol;
	                return true;
	            }
	            
	            //double space move (only valid from starting position)(White)
	            if(originRow == 1){ //if the pawn is in the starting row
	                if(originRow + 2 == destRow && originCol == destCol) {
	                	originRow = destRow;
	            		originCol = destCol;
	                    return true;
	                }
	            }
	            
	            //double space move (only valid from starting position)(Black)
	            if(originRow == 1){ //if the pawn is in the starting row
	                if(originRow + 2 == destRow && originCol == destCol) {
	                	originRow = destRow;
	            		originCol = destCol;
	                    return true;
	                }
	            }
			}
			
            //There is checking whether there is a piece or not. So if it is a nullptr(no piece), then you will not be able make the move. 
            else
            {
	            //diagonal capture move
	            if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol)) && (board[destRow][destCol] ->isBlackCheck() != this->isBlackCheck())) {
	            	originRow = destRow;
            		originCol = destCol;
	                return true;
	            }
			}
            return false;
        	
        }

        //Pawn class's destructor
        Pawn::~Pawn()
        {
            std::cout << "Pawn has been captured" << std::endl;
        }
