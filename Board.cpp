#include "Board.h"

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
            
            
            if(board[destRow][destCol] != nullptr)
            {
                std::cout << "The destination is already occupied. Try another destination.";
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
                // destination is not null(because checked previously), so we can straight away move the piece and capture the attacked piece
                {
                    if (chosenPiece->isBlackCheck())
                    {
                        invertBoard();
                        
                        //inverting the coordinates so that they would work for black 
                        destRow = 7 - destRow;
                        destCol = 7 - destCol;
                        originRow = 7 - originRow;
                        originCol = 7 - originCol;
                    }
                        
                    
                    // if capturing move, delete the opposing piece
                    // doublecheck if piece to be captures is of opposing color
                    if (originRow + 2 == destRow && board[(destRow + originRow) / 2][(destCol + originCol) / 2]->isBlackCheck() != chosenPiece->isBlackCheck())
                    {
                        delete board[(destRow + originRow) / 2][(destCol + originCol) / 2];
                        board[(destRow + originRow) / 2][(destCol + originCol) / 2] = nullptr;
                    }
                    
                    else if ((originRow + 2 == destRow && board[(destRow + originRow) / 2][(destCol + originCol) / 2]->isBlackCheck() == chosenPiece->isBlackCheck()))
                    {
                        std::cout << "Can not capture same color piece. Try again";
                        return;
                    }
                    
                    if (chosenPiece->isBlackCheck())
                    {
                        invertBoard();
                        
                        // inverting back to normal coordinates
                        destRow = 7 - destRow;
                        destCol = 7 - destCol;
                        originRow = 7 - originRow;
                        originCol = 7 - originCol;
                    }
                    
                    // assign the piece to new location and empty the previous location
                    board[destRow][destCol] = board[originRow][originCol];
                     
                    // reset the pointer to null
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

