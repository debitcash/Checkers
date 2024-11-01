#include <iostream>
#include "Pawn.cpp"
//#include "Piece.cpp"
//#include <typeinfo>


class Board{

    private:
        // declare the board and initialize the board values
        Pawn* board[8][8] = {
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}, // black pieces
            {new Pawn(false, 1, 0), new Pawn(false, 1,1), new Pawn(false, 1,2),
                new Pawn(false,1,3), new Pawn(false, 1,4), new Pawn(false,1,5),
                new Pawn(false, 1,6), new Pawn(false, 1,7)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
            {new Pawn(true,6,0), new Pawn(true, 6,1), new Pawn(true, 6, 2),
            new Pawn(true, 6,3), new Pawn(true, 6, 4), new Pawn(true, 6, 5),
            new Pawn(true,6, 6), new Pawn(true, 6, 7)},
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}; // white pieces

    public:
        void move(int originRow, int originCol, int destRow, int destCol, int& turn)
        {
            bool valid;

            //user's idea of the board and the array are flipped, something need to be adjust for this.
            

            //figure out what piece is at origin position
            Pawn* piece = board[originRow][originCol];

            if(piece->isBlackCheck()) {
                //invert the orign and dest rows/cols
            }

            valid = piece->isValidMove(destRow, destCol);

            if(piece->isBlackCheck()) {
                //revert the origin and dest rows/cols
            }

            //needs some kind of loop to deal with non-valid moves and user trying again
            if(valid == true) {
                piece->move(destRow, destCol, board[destRow][destCol], board);
                turn++;
            }
            else
                std::cout << "That was not a valid move, try again." << std::endl;


            // // check if chosen location has a present piece on it
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
             * 
             *  if (piece == typeid(Pawn))
             *  {
             *      Pawn& pawn = piece;
             *      
             *      if (piece.isBlack == true )
             *      {
             *          check caption options below the piece for diagonal move;
             *          
             *          bool whiteOnLeft = !(Board[row + 1][column - 1] -> isBlack); // pay attention to out of board locations here=> ((column -1 > 0) && (row + 1 < 8)) ? !(Board[row + 1][column - 1] -> isBlack) : false;
            *          bool whiteOnRight = !(Board[row + 1][column + 1] -> isBlack);
             *          
             *          pawn.isValidMove(row1, column1, row2, column2, whiteOnLeft, whiteOnRight);
             *      }
             * 
             *      else
             *      {   
             *          check caption options above the piece for diagonal move;
             * 
             *          bool blackOnLeft = !(Board[row - 1][column - 1] -> isBlack);
             *          bool blackOnRight = !(Board[row - 1][column + 1] -> isBlack);
             *          
             *          pawn.isValidMove(row1, column1, row2, column2, blackOnLeft, blackOnRight);
             *      }
             *  }
             * 
             *  else
             *  {
             *      return piece.isValidMove();
             *  }
             * 
             * */
            //
            // // assign the piece to new location and empty the previous location
            // board[destRow][destCol] = board[originRow][originCol];
            // // delete the object here?
            // board[originRow][originCol] = nullptr;
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
