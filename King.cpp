#include "King.h"
#include "Piece.h"
#include <iostream>

King::King(bool newColour, bool newStatus, int newRow, int newCol) :  Piece(newColour, newStatus), originRow(newRow),originCol(newCol) {}
    	
bool King::isValidMove(int destRow, int destCol, Piece* board[8][8]) 
	   {
	   		//all moves are valid if we are moving within 1 square
			if ((destRow == originRow + 1 || destRow == originRow - 1 || destRow == originRow) &&
				(destCol == originCol + 1 || destCol == originCol - 1) || destCol == originCol)
			{
				return true;
			}
			
			else
				return false;
		
	   }