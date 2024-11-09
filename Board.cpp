#include <iostream>
#include "Pawn.h"
#include "Pawn.cpp"
#include "Piece.cpp" //added
//#include <typeinfo>
//#include "Piece.cpp"
//#include <typeinfo>


class Board{

    private:
        // declare the board and initialize the board values
        //(CHANGE: Jaisung) I have added that the board is now of a piece class, so it should take all of them.
        Piece* board[8][8] = {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, // white pieces
            {new Pawn(false,false, 1, 0), new Pawn(false, false, 1, 1), new Pawn(false,false, 1,2),
                new Pawn(false,false,1,3), new Pawn(false,false, 1,4), new Pawn(false,false,1,5),
                new Pawn(false,false, 1,6), new Pawn(false, false, 1,7)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {new Pawn(true, false, 6,0), new Pawn(true, false, 6,1), new Pawn(true, false, 6, 2),
            new Pawn(true, false,  6,3), new Pawn(true, false, 6, 4), new Pawn(true, false, 6, 5),
            new Pawn(true, false, 6, 6), new Pawn(true, false, 6, 7)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}; // black pieces
        

    public:
        /*void move(int originRow, int originCol, int destRow, int destCol, int& turn)
        {
            bool valid;


            //user's idea of the board and the array are flipped, something need to be adjust for this.
                    
            //figure out what piece is at origin position
            //(CHAGE:JAISUNG) I had to dynamically cast this to the pawn class or else it couldn't use "move" properly 
            Pawn* piece = dynamic_cast<Pawn*>(board[originRow][originCol]);


        

            if(piece->isBlackCheck()) {
                //invert the orign and dest rows/cols
                invertBoard();
                valid = piece->isValidMove(7 - destRow, 7 - destCol, board);
            }
            

            else
            {
            	valid = piece->isValidMove(destRow, destCol, board);
			}
            

            //Inversion to destination. 
            valid = piece->isValidMove(7 - destRow, 7 - destCol);

            if(piece->isBlackCheck()) {
                //revert the origin and dest rows/cols
                invertBoard();
            }

            //needs some kind of loop to deal with non-valid moves and user trying again
            if(valid == true) {
                piece->move(destRow, destCol, board[destRow][destCol], board);
                turn++;

            }/*
            else if () //This would be the piece collision case 
            {
                
            }
            else if () //This would be the king is checked case.

            }

            else
                std::cout << "That was not a valid move, try again." << std::endl;*/

            // check if chosen location has a present piece on it
            // if (board[originRow][originCol] == nullptr)
            // {
            //     std::cout << "There is no piece present at this square";
            //     return;
            // }
            //
            // // check if its the user trying to move their respective color
            // if (! ((board[originRow][originCol]->isBlackCheck() && turn % 2 ==0) || (!board[originRow][originCol]->isBlackCheck() && turn % 2 != 0)))
            // {
            //     std::cout << "You should move other color at current turn";
            //     return;
            // }

            /* Trying to figure out how to enable diagonal moves for pond in this comment section
             *  Piece& piece = *board[row1][column1];
             */


 
            // // assign the piece to new location and empty the previous location
            // board[destRow][destCol] = board[originRow][originCol];
            // // delete the object here?
            // board[originRow][originCol] = nullptr;
        //}
        
        //Just testing a new move that maybe the board could check versues making each piece check itself 
        //Going back to the idea that each class should only contain its own logic not the whole board logic. 
        void newMove(int originRow, int originCol, int destRow, int destCol, int& turn)
        {
            bool valid; 
            //Allowing the chosen "Piece to be put at the origin"
            Piece* chosenPiece = board[originRow][originCol];
            
           // Pawn* chosenPiece = dynamic_cast<Pawn*>(board[originRow][originCol]);

            
        	if(chosenPiece->isBlackCheck()) 
			{
                //invert the orign and dest rows/cols
                invertBoard();
                valid = chosenPiece->isValidMove(7 - destRow, 7 - destCol, board);
           	}
            else
            {
            	//Inversion to destination. 
            	valid = chosenPiece->isValidMove(destRow, destCol, board);
			}
            

            if(chosenPiece->isBlackCheck()) 
			{
                //revert the origin and dest rows/cols
            	invertBoard();
           	}
            
            if (valid == false)
            	{
            		std::cout << "Wrong move";
            		return;
				}
            
            //The idea behind this move function is that the board will actually move and think about the other pieces on the board. 
            //The pieces will just provide the logic of what they know, this will allow less coupling with other pieces.
            if(valid == true)
            {
                //This is going to be the capture logic when the board "senses" another piece is on the destination point
                if(board[destRow][destCol] != nullptr && chosenPiece->isBlackCheck() != board[destRow][destCol] -> isBlackCheck())
                {
                    //Delete the old piece, capturing it. It should call the destructor and that will allow it to message that the piece is destroyed.
                    delete board[destRow][destCol];
                    
                    //assign the piece to the new location 
                    board[destRow][destCol] = board[originRow][originCol];
                    
                    // assign the original area to null here.
                    board[originRow][originCol] = nullptr;

                    originRow = destRow;
                    originCol = destCol;
                }
                
                //this is now going to be the case where the board place is empty
                else if (board[destRow][destCol] == nullptr)
                {
                    // assign the piece to new location and empty the previous location
                    board[destRow][destCol] = board[originRow][originCol];
                    // delete the object here?
                    board[originRow][originCol] = nullptr;

                    originRow = destRow;
                    originCol = destCol;
                }
                
            }
            else
            {
                std::cout << "This move isn't valid, please try again.";
            }
            
            
        }
        
        
        void invertBoard()
        {
        	
        	for (int row = 0; row < 4; row++)
        	{
        		for (int column = 0; column < 8; column++)
        		{
        			Piece* temp = board[row][column];
        			
        			board[row][column] = board[7 - row][7 - column];
        			
        			board[7 - row][7 - column] = temp;
        			
        			if (row == 3 && column == 7)
        				break;
				}
			}
        	
		}
        
        // display the board
        void display()
        {
            for (int y = 0; y < 8; y++)
            {
                for (int x = 0; x < 8; x++)
                {
                    if (board[y][x] == nullptr)
                    {
                        std::cout << "0 ";
                    }
                    else
                    {
                        std::cout << "P ";
                    }
                }
                
                std::cout << std::endl;
            }
        }

};

