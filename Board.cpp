#include "Board.h"
#include <vector>
#include <sstream>
//allows for colour usability
//#include <windows.h>

//parses a string into 2 pairs of ints
std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > parseMove(const std::string& moves);

// distinguishing between multiplehops and jus one move here
void Board::attemptMove(std::string input, int& turn)
{
    // store multiple hops here, provided by parse function
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > moveSequence = parseMove(input);
    
    // do regular move if only one move/hop provided
    if (moveSequence.size() == 1)
    {
        this->move(moveSequence[0], turn);
    }
        
        
    else
    {
        // if multiple moves provided and they ALL are valid
        if (isSequenceValid(moveSequence))
        {
            // for each move in a sequence do it with our regular move function
            for (std::pair<std::pair<int, int>, std::pair<int, int> >  coordinates : moveSequence)
            {
                std::cout << "Checking coordinates \n"; 
                this->move(coordinates, turn);
                // minus turn, because move function increments the turn after its done
                turn--;
            }
            
            turn++;
        }
        else
            std::cout << "Sequence is invalid, try other path \n"; 
        
    }
    
    
    
    // if sucessfully moved the piece continue to next player
    //if (board[moveSequence[0].first.first][moveSequence[0].first.second] == nullptr)
      //  turn++;
    
}

//checks the sequence for valididty of moves(LOTS of duplicate code)
bool Board::isSequenceValid(std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >  sequence)
{
    //stores current piece on drigin coordinates
    Piece* chosenPiece = board[sequence[0].first.first][sequence[0].first.second];
    
    //for each coordinate pairs(orig, dest)
    for (std::pair<std::pair<int, int>, std::pair<int, int> >  coordinates : sequence)
    {
        
        int originRow = coordinates.first.first;
        int originCol = coordinates.first.second;
        int destRow = coordinates.second.first;
        int destCol = coordinates.second.second;
        
        
        //Piece* chosenPiece = board[originRow][originCol];
        
        if(chosenPiece->isBlackCheck())
        {
            invertBoard();
            destRow = 7 - destRow;
            destCol = 7 - destCol;
            originRow = 7 - originRow;
            originCol = 7 - originCol;
        }
        std::cout << "CHECK\n";
        // identifies when user tries to jump over nonexistent piece, or when tries to move 1 squareat time
        // the detection of one square movement appeared like a bug, because the curent calculation gonna give the location of a square that can never contain a piece
        //which is a good thing for this case, as far as we are trying to not let single square moves in sequence moves; but just keep that in mind
        if (board[(destRow + originRow) / 2][(destCol + originCol) / 2] == nullptr)
        {
            std::cout << "Don't try to hop over nothing, or attempt single moves in a hop sequence.\n";
            if(chosenPiece->isBlackCheck())
            {
                invertBoard();
            }
            
            return false;
        }
        
        // check if hopping over the same color
        if (originRow + 2 == destRow && board[(destRow + originRow) / 2][(destCol + originCol) / 2]->isBlackCheck() == chosenPiece->isBlackCheck())
        {
            std::cout << "Can't take out same colors\n"; 
            if(chosenPiece->isBlackCheck())
            {
                invertBoard();
            }
            return false;
        }
        //else if(originRow + 1 ==destRow)
          //  return false;
        
        if(chosenPiece->isBlackCheck())
        {
            invertBoard();
        }
        
        
        
    }
        
    
    
    return true;
}


//Going back to the idea that each class should only contain its own logic not the whole board logic.
void Board::move(/*int originRow, int originCol, int destRow, int destCol,*/std::pair<std::pair<int, int>, std::pair<int, int> > move, int& turn)
{
        
        int originRow = move.first.first;
        int originCol = move.first.second;
        int destRow = move.second.first;
        int destCol = move.second.second;

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

        //checking for various errors with the coordinate input
        if(checkForError(originRow,originCol, destRow, destCol, turn, chosenPiece)) {
            return;
        }

        //if the chosen piece is black, invert the board
        if(chosenPiece->isBlackCheck())
        {
            //invert the origin and dest rows/cols
            invertBoard();
            valid = chosenPiece->isValidMove(7 - destRow, 7 - destCol /*, board*/);
            //revert the origin and dest rows/cols
            invertBoard();
        }else{
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

                // check if trying to hop over empty square
                if (board[(destRow + originRow) / 2][(destCol + originCol) / 2] == nullptr && destRow == originRow + 2)
                {
                    std::cout << "Can't hop over nothing\n";
                    if (chosenPiece->isBlackCheck())
                    {
                        invertBoard();
                    }
                    return;
                }
                    
                
                // if capturing move, delete the opposing piece
                // doublecheck if piece to be captured is of opposing color
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
            
            chosenPiece->setOriginCol(destCol);
            chosenPiece->setOriginRow(destRow);
            
            if (chosenPiece->isBlackCheck())
                {
                    chosenPiece->setOriginCol(7 - destCol);
                    chosenPiece->setOriginRow(7 - destRow);
                }
            
            this->display();

            
        }

        else
        {
            std::cout << "This move isn't valid, please try again." << std::endl;
            return;
        }
        
        turn++;
}

//inverts the board so that red and black moves can be handled the same way
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
/*
// display the board
void Board::display()
{
    //allows for colour printout in the terminal
    system(("chcp " + std::to_string(CP_UTF8)).c_str());

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
*/

bool Board::checkForError(int originRow, int originCol, int destRow, int destCol, const int& turn, const Piece* chosenPiece) {
    bool error = false;

    //origin location outside of board
    if (originRow > 7 || originRow < 0 || originCol > 7 || originCol < 0 )
    {
        std::cout << "The origin location is outside the board boundary, choose a valid origin." << std::endl;
        error = true;
    }

    //destination location outside board
    else if (destRow > 7 || destRow < 0 || destCol > 7 || destCol < 0)
    {
        std::cout << "The chosen destination is outside the board boundary, choose a valid destination." << std::endl;
        error = true;
    }

    //origin and destination are the same
    else if (destRow == originRow && destCol == originCol)
    {
        std::cout << "You provided the same coordinates, they have to be different." << std::endl;
        error = true;
    }

    //the destination location has a piece at it already
    if(board[destRow][destCol] != nullptr)
    {
        std::cout << "This destination is already occupied. Try another destination.";
        error = true;
    }

    //Attempting to move black piece on red's turn
    if (turn % 2 != 0 && chosenPiece->isBlackCheck())
    {
        std::cout << "Not your turn! Move red pieces now." << std::endl;
        error = true;
    }

    //Attempting to move red piece on black's turn
    else if (turn % 2 == 0 && !chosenPiece->isBlackCheck())
    {
        std::cout << "Not your turn! Move black pieces now." << std::endl;
        error = true;
    }

    return error;

}

//parses the inputted string into 2 pairs of ints. the first pair is the initial row & col, second is the destination row & col
std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > parseMove(const std::string& moves)
{
        // array that stores all pairs
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > parsedMoves;
        
        std::stringstream movesStream(moves);
        std::vector<std::string> rawMoves;
        std::string move;
        
        // splits the string using whitespaces
        while(std::getline(movesStream, move, ' '))
        {
           rawMoves.push_back(move);
           
        }

        for (std::string stringMove: rawMoves) 
        {
            
            if (stringMove.size() != 5 || stringMove[2] != '>') 
            {
                parsedMoves.push_back(std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1)));
                continue;
            }

            //adjusts the input for the board's handling of coordinates
            int originCol = stringMove[0] - 'a';
            int originrow = stringMove[1] - '1';
            int destCol = stringMove[3] - 'a';
            int destrow = stringMove[4] - '1';

            parsedMoves.push_back({{originrow, originCol}, {destrow, destCol} });
            
        }
        
        /*for (const auto& move : parsedMoves) {
            std::cout << "Origin: (" << move.first.first << ", " << move.first.second << "), "
                  << "Destination: (" << move.second.first << ", " << move.second.second << ")\n";
        }*/
        
     return parsedMoves;
}

