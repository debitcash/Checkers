#include "Board.h"
//allows for colour usability
#include <windows.h>

        //Going back to the idea that each class should only contain its own logic not the whole board logic. 
        void Board::move(int originRow, int originCol, int destRow, int destCol, int& turn)
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
                std::cout << "Wrong piece, move red pieces now." << std::endl;
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
                //board assigns piece to destination position, null at origin
                //board needs to check if a piece was jumped over/captured on the path, and remove that piece
                //wonder if there's a way to find coordinate between dest and orgin on diagonal?
                //assign that board spot to null
                //This is going to be the capture logic when the board "senses" another piece is on the destination point
                if(board[destRow][destCol] != nullptr && chosenPiece->isBlackCheck() != board[destRow][destCol] -> isBlackCheck())
                {
                    //Delete the old piece, capturing it. It should call the destructor and that will allow it to message that the piece is destroyed.
                    delete board[destRow][destCol];
                    
                    //assign the piece to the new location 
                    board[destRow][destCol] = board[originRow][originCol];
                    
                    // assign the original area to null here.
                    board[originRow][originCol] = nullptr;
                }
                
                //this is now going to be the case where the board place is empty
                else if (board[destRow][destCol] == nullptr)
                {
                    // assign the piece to new location and empty the previous location
                    board[destRow][destCol] = board[originRow][originCol];
                    // delete the object here
                    // delete the object here
                    board[originRow][originCol] = nullptr;
                }
                
                // display the board after move was made
                this->display();
                
                turn++;
            }
            
            else
            { 
                std::cout << "This move isn't valid, please try again." << std::endl;
            } 
        }
        
        
        void Board::invertBoard()
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
        void Board::display()
        {
            system(("chcp " + std::to_string(CP_UTF8)).c_str());

            for (int y = 0; y < 8; y++)
            {
                std::cout << y + 1 << " | ";
                for (int x = 0; x < 8; x++)
                {
                    if (board[y][x] == nullptr)
                    {
                        /*//prints checkerboard pattern
                        if(y % 2 == 0) {
                            if(x % 2 == 0) {
                                std::cout << "\u25A0 ";
                            }
                            else {
                                //std::cout << "  ";
                                std::cout << "\u25A1 ";
                            }

                        }
                        else {
                            if(x % 2 != 0) {
                                std::cout << "\u25A0 ";
                            }
                            else {
                                //std::cout << "  ";
                                std::cout << "\u25A1 ";
                            }

                        }*/

                        std::cout << ". ";
                    }
                    else if (board[y][x]->isBlackCheck())
                    {
                        //std::cout << "b ";
                        std::cout << "\033[34m\u25CF\033[0m ";
                    }
                    
                    else if (!board[y][x]->isBlackCheck())
                    {
                        //std::cout << "r ";
                        std::cout << "\033[31m\u25CF\033[0m ";
                    }
                    
                }
                std::cout << std::endl;
            }
            std::cout << "--+-----------------" << std::endl;
            std::cout << "  | a b c d e f g h" << std::endl;
        }

