#include "Pawn.h"
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
       bool Pawn::isValidMove(int destRow, int destCol, Piece* board[8][8]) 
	   {
            //single space move
            if(originRow + 1 == destRow && originCol == destCol) {
                return true;
            }
            
            
            
            //double space move (only valid from starting position)(White)
            if(originRow == 2){ //if the pawn is in the starting row
                if(originRow + 2 == destRow && originCol == destCol) {
                    return true;
                }
            }
            
            //double space move (only valid from starting position)(Black)
            if(originRow == 7){ //if the pawn is in the starting row
                if(originRow + 2 == destRow && originCol == destCol) {
                    return true;
                }
            }

            //There is checking whether there is a piece or not. So if it is a nullptr(no piece), then you will not be able make the move. 
            if(board[destRow][destCol] != nullptr)
            {
	            //diagonal capture move
	            if((originRow + 1 == destRow) && ((originCol + 1 == destCol) || (originCol - 1 == destCol)) && (board[destRow][destCol] ->isBlackCheck() != this->isBlackCheck())) {
	                return true;
	            }
			}
            return false;
        	
        }

       /* void Pawn::move(int destRow, int destCol, Piece* piece, Piece* board[8][8]) {

            //Capture logic
            //Should check whether a piece exists or not, which it won't if it equals a nullptr and also checking whether the isBlackCheck do not match to determine if they are both different colours. 
            if(board[destRow][destCol] != nullptr && piece->isBlackCheck() != board[destRow][destCol]->isBlackCheck())
            //have not implemented the king check yet. 
            {
                //deleting the old piece, it should call the destructor so the destructor will call it being "captuared"
                delete board[destRow][destCol];
                //assign the piece to the new location 
                board[destRow][destCol] = board[originRow][originCol];


                // assign the original area to null here.
                board[originRow][originCol] = nullptr;

                originRow = destRow;
                originCol = destCol;
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
            
            
           }*/

        //Pawn class's destructor
        Pawn::~Pawn()
        {
            std::cout << "Pawn has been captured" << std::endl;
        }