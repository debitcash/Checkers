#include <iostream>
#include "Pawn.cpp"
//#include <typeinfo>

class Board{
    private:
        // declare the board and initialize the board values
        Pawn* board[8][8] = {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, // black pieces
            {new Pawn(true), new Pawn(true), new Pawn(true), new Pawn(true), new Pawn(true), new Pawn(true), new Pawn(true), new Pawn(true)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {new Pawn(false), new Pawn(false), new Pawn(false), new Pawn(false), new Pawn(false), new Pawn(false), new Pawn(false), new Pawn(false)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}; // white pieces
        
    public:
        void move(int row1, int column1, int row2, int column2, int& turn)
        {
            // check if chosen location has a present piece on it
            if (board[row1][column1] == nullptr)
            {
                std::cout << "There is no piece present at this square";
                return;
            }
            
            // check if its the user trying to move their respective color
            if (! ((board[row1][column1]->isBlackCheck() && turn % 2 ==0) || (!board[row1][column1]->isBlackCheck() && turn % 2 != 0)))
            {
                std::cout << "You should move other color at current turn";
                return;
            }
            
            /* Trying to figure out how to enable diagonal moves for pond here
             *  Piece& piece = *board[row1][column1];
             * 
             *  if (piece == typeid(Pawn))
             *  {
             *      if (piece.isBlack == true)
             *      {
             *          check caption options below the piece for diagonal move;
             *      }
             * 
             *      else
             *      {   
             *          check caption options above the piece for diagonal move;
             *      }
             *  }
             * 
             *  else
             *  {
             *      return piece.isValidMove();
             *  }
             * 
             * */
            
            // assign the piece to new location and empty the previous location
            board[row2][column2] = board[row1][column1];
            // delete the object here?
            board[row1][column1] = nullptr;
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
