#include <iostream>
#include "Checker.h"
#include "Piece.h"

#include <cmath>

class Board{

    private:
        // declare the board and initialize the board values
        //(CHANGE: Jaisung) I have added that the board is now of a piece class, so it should take all of them.
        Piece* board[8][8] = {
            {nullptr, new Checker(false, false, 0, 1), nullptr, new Checker(false, false, 0, 3), 
                nullptr, new Checker(false, false, 0, 5), nullptr, new Checker(false, false, 0, 7)}, // RED pieces
            {new Checker(false, false, 1, 0), nullptr, new Checker(false, false, 0, 2), nullptr, 
                new Checker(false, false, 0, 4), nullptr, new Checker(false, false, 0, 6), nullptr},
            {nullptr, new Checker(false, false, 2, 1), nullptr, new Checker(false, false, 2, 3), 
                nullptr, new Checker(false, false, 2, 5), nullptr, new Checker(false, false, 2, 7)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {new Checker(true, false, 5, 0), nullptr, new Checker(true, false, 5, 2), nullptr, 
                new Checker(true, false, 5, 4), nullptr, new Checker(true, false, 5, 6), nullptr},
            {nullptr, new Checker(true, false, 6, 1), nullptr, new Checker(true, false, 6, 3), nullptr, 
                new Checker(true, false, 6, 5), nullptr, new Checker(true, false, 6, 7)},
            {new Checker(true, false, 7, 0), nullptr, new Checker(true, false, 7, 2), nullptr, 
                new Checker(true, false, 7, 4), nullptr, new Checker(true, false, 7, 6), nullptr}}; // black pieces
        
    public:
    
        //Going back to the idea that each class should only contain its own logic not the whole board logic. 
        void move(int originRow, int originCol, int destRow, int destCol, int& turn)
        {
            if (originRow > 7 || originRow < 0 || originCol > 7 || originCol < 0 )
            {
                std::cout << "The origin location is outside the board boundary, choose a valid origin." << std::endl;
                return;
            }
            
            else if (destRow > 7 || destRow < 0 || destCol > 7 || destCol < 0)
            {
                std::cout << "The chosen destination is outside the board boundary, choose a valid destination." << std::endl;
                return;
            }
            
            else if (destRow == originRow && destCol == originCol)
            {
                std::cout << "You provided same coordinates, they have to be different." << std::endl;
                return;
            }
            
            bool valid = true; 
            Piece* chosenPiece;
            
            //Allowing the chosen "Piece to be put at the origin" 
            if (board[originRow][originCol] != nullptr)
                chosenPiece = board[originRow][originCol];
            else
            {
                std::cout << "There is no piece at the chose location." << std::endl;
                return;
            }
            
            if (turn % 2 != 0 && chosenPiece->isBlackCheck())
            {
                std::cout << "Wrong piece, move white pieces now." << std::endl;
                return;
            }
            
            else if (turn % 2 == 0 && !chosenPiece->isBlackCheck())
            {
                std::cout << "Wrong piece, move black pieces now." << std::endl;
                return;
            }
            
        	if(chosenPiece->isBlackCheck()) 
			{
                //invert the orign and dest rows/cols
                invertBoard();
                valid = chosenPiece->isValidMove(7 - destRow, 7 - destCol /*, board*/);
                //revert the origin and dest rows/cols
            	invertBoard();
           	}
            
            else
            {
            	//Inversion to destination. 
            	valid = chosenPiece->isValidMove(destRow, destCol /*,board*/);
			}

            //The idea behind this move function is that the board will actually move and think about the other pieces on the board. 
            //The pieces will just provide the logic of what they know, this will allow less coupling with other pieces.
            if(valid == true)
            {

                
                // display the board after move was made
                this->display();
                
                turn++;
            }
            
            else
            { 
                std::cout << "This move isn't valid, please try again." << std::endl;
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
                std::cout << y + 1 << " | ";
                for (int x = 0; x < 8; x++)
                {
                    if (board[y][x] == nullptr)
                    {
                        std::cout << ". ";
                    }
                    else if (board[y][x]->isBlackCheck())
                    {
                        std::cout << "b ";
                    }
                    
                    else if (!board[y][x]->isBlackCheck())
                    {
                        std::cout << "r ";
                    }
                    
                }
                std::cout << std::endl;
            }
            std::cout << "--+-----------------" << std::endl;
            std::cout << "  | a b c d e f g h" << std::endl;
        }
};

