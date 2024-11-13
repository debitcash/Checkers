#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece
{
	private: 
	    int originRow;
	    int originCol;
    
    public:
    	bool isValidMove(int, int, Piece* board[8][8]);
    	
    	King();
    	
    	King(bool, bool, int, int);
    	
    
};

#endif 