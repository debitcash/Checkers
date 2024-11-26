#include "Board.h"
#include <vector>
#include <sstream>
#include <typeinfo>

// class that is responsible for all the piece movements on the board, and visually displaying the game

// allows for colour usability
//#include <windows.h>

void invertCoordinates(int& originRow, int& originCol, int& destRow, int& destCol);

// parses string coordinates into a vector of int pairs
std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > parseMove(const std::string& moves);

// attempt to make a move to provided coordinates
void Board::attemptMove(std::string input, int& turn)
{
    // store the entered moves, provided by parse function. Can be either 1 move, or multiple hops
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > moveSequence = parseMove(input);

    // check if user did not provide any coordinates at all
    if (moveSequence.size() == 0)
    {
        std::cout << "You did not provide any coordinates, please try again." << std::endl;
        return;
    }
        
    // get coordinates of first move in the from the entered sequence
    int originRow = moveSequence[0].first.first;
    int originCol = moveSequence[0].first.second;
    int destRow = moveSequence[0].second.first;
    int destCol = moveSequence[0].second.second;
    
    // get the element that is selected for a move
    Piece* chosenPiece = board[originRow][originCol];
    
    // check if any errors are associated with the first in sequence (or only one) move
    if (checkForError(originRow, originCol, destRow, destCol, turn, board[originRow][originCol]))
    {
        return ;
    }

    bool isBlack = chosenPiece->isBlackCheck();

    // invert board and coordinates if the piece is black
    if(isBlack)
    {
        invertBoard();
        invertCoordinates(originRow, originCol, destRow, destCol);
    }
    
    // do regular move if only one square move provided, or a sequence where the first move is one square move
    // we don't care about the next move, because only hops can be provided in multiple moves sequence
    if (originRow + 1 == destRow  &&  chosenPiece->isValidMove(destRow, destCol ))
    {
        // provide new locations for the moved checker
        board[destRow][destCol] = board[originRow][originCol];
        board[originRow][originCol] = nullptr;
        
        // provide the new coordinates for a piece
        board[destRow][destCol]->setOriginCol(destCol);
        board[destRow][destCol]->setOriginRow(destRow);
        
        std::cout << "The piece has moved to row " << destRow << " and the column moved to " << destCol << std::endl;
        
        // check if we should promote a piece after a move
        checkPromotion(destRow,destCol);
    }
    
    // different checking logic for a kingChecker single move
    else if (originRow - 1 == destRow && chosenPiece-> isValidMove(destRow, destCol) && typeid(*chosenPiece) == typeid(KingChecker) )
    {
        // provide new location for the moved checker
        board[destRow][destCol] = board[originRow][originCol];
        board[originRow][originCol] = nullptr;
        
        // provide the new coordinates for a piece
        board[destRow][destCol]->setOriginCol(destCol);
        board[destRow][destCol]->setOriginRow(destRow);
        
        std::cout << "This piece has moved to row " << destRow << " and the column moved to" << destCol <<std::endl;
        
        // don't need to check promotion for kingChecker since its already kingChecker 
    }
    
    // process when there were more that one hop provided
    else
    {
        // create variables that are going to track whether the moves actually follow a chain of one piece movement
        // otherwise, user will be able to move two different pieces at same time
        int previousHopRow = -1;
        int previousHopCol = -1;
        
        // repeat for each pair in a user provided sequence
        for (std::pair<std::pair<int, int>, std::pair<int, int> > coordinates : moveSequence)
        {
            // get coordinates for the move from movesequence
            int originRow = coordinates.first.first;
            int originCol = coordinates.first.second;
            int destRow = coordinates.second.first;
            int destCol = coordinates.second.second;
            
            // invert coordinates for black piece, because they are updated every time a new move is taken from hop sequence
            if(isBlack)
            {
                invertCoordinates(originRow, originCol, destRow, destCol);
            }
            
            // if piece is not following the move chain, let the user do only first valid move
            if (!((originRow == previousHopRow && originCol == previousHopCol) || (previousHopRow == -1 && previousHopCol == -1)))
            {
                std::cout << "You are attempting to move different pieces at same time, only first move was executed." << std::endl;
                
                if(chosenPiece->isBlackCheck())
                    invertBoard();
                    
                return ;
            }
            
            // checking for errors, because new coordinates are provided for each new hop
            if (checkForError(originRow, originCol, destRow, destCol, turn, chosenPiece))
            {
                if(chosenPiece->isBlackCheck())
                    invertBoard();
                return ;
            }
            
            // do captureMoveCheck
            if (!captureMoveCheck(originRow, originCol, destRow, destCol, turn))
            {
                if(chosenPiece->isBlackCheck())            
                    invertBoard();
                return;
            }
            
            // do the cleanup of captured piece after the hop
            delete board[(destRow + originRow) / 2][(destCol + originCol) / 2];
            board[(destRow + originRow) / 2][(destCol + originCol) / 2] = nullptr;
            
            // update location of the hopping piece
            board[destRow][destCol] = board[originRow][originCol];
            board[originRow][originCol] = nullptr; 
            
            // set new coordinates in the hopping piece
            board[destRow][destCol]->setOriginCol(destCol);
            board[destRow][destCol]->setOriginRow(destRow);
            
            std::cout << "The piece has moved to row " << destRow << " and the column moved to " << destCol << std::endl;
            
            checkPromotion(destRow,destCol);
            
            // update the markers to track the hopping path
            previousHopRow = destRow;
            previousHopCol = destCol;
        }
    }

    // invert the board back to return to original board orientation
    if(isBlack)
    {
        invertBoard();
    }
    
    // proceed to next turn
    turn++;
}

// checks the hop move
bool Board::captureMoveCheck(int originRow, int originCol, int destRow, int destCol, int& turn)
{
    // piece to be checked
    Piece* chosenPiece = board[originRow][originCol];
    
    // check by overloaded checker class member function
    if (!chosenPiece->isValidMove(destRow, destCol))
    {
        std::cout << "Wrong move for a checker, detected in checker member function" << std::endl;
        return false;
    }
        
    // check if user tries to do a single move after a hop
    if (destRow == originRow + 1)
    {
        std::cout << "Don't attempt single moves in a hop sequence, only hop move was made.\n";
        turn++;
        return false;
    }
    
    // check if it is going backwards. (King Movement)
    if (destRow == originRow - 1)
    {
        std::cout << "Don't attempt single moves in a hop sequence, only hop was made. \n";
        turn++; 
        return false; 
    }
    
    // check if user tries to jump over empty square
    if (board[(destRow + originRow) / 2][(destCol + originCol) / 2] == nullptr)
    {
        std::cout << "Don't try to hop over nothing\n";
        return false;
    }
        
    // check if user tries to capture a same color piece
    if (originRow + 2 == destRow && board[(destRow + originRow) / 2][(destCol + originCol) / 2]->isBlackCheck() == chosenPiece->isBlackCheck())
    {
        std::cout << "Can't capture same colors" << std::endl; 
        return false;
    }
    
    return true;
}

// inverts the board so that red and black moves can be handled the same way
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

// display the board in terminal
void Board::display() const {
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
// display the board in terminal
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

// a coolection of user input error checks
bool Board::checkForError(int originRow, int originCol, int destRow, int destCol, const int& turn, const Piece* chosenPiece) 
{
    // origin location outside of board
    if (originRow > 7 || originRow < 0 || originCol > 7 || originCol < 0 )
    {
        std::cout << "The origin location is outside the board boundary, choose a valid origin." << std::endl;
        return true;
    }

    // destination location outside board
    else if (destRow > 7 || destRow < 0 || destCol > 7 || destCol < 0)
    {
        std::cout << "The chosen destination is outside the board boundary, choose a valid destination." << std::endl;
        return true;
    }

    //origin and destination are the same
    else if (destRow == originRow && destCol == originCol)
    {
        std::cout << "You provided the same coordinates, they have to be different." << std::endl;
        return true;
    }
    
    // the destination location has a piece at it already
    if(board[destRow][destCol] != nullptr)
    {
        std::cout << "This destination is already occupied. Try another destination." << std::endl;
        return true;
    }
    
    // chosen an empty square
    if(chosenPiece == nullptr)
    {
        std::cout << "You have chosen an empty square." << std::endl;
        return true;
    }
    
    // attempting to move black piece on red's turn
    if (turn % 2 != 0 && chosenPiece->isBlackCheck())
    {
        std::cout << "Not your turn! Move red pieces now." << std::endl;
        return true;
    }

    // attempting to move red piece on black's turn
    else if (turn % 2 == 0 && !chosenPiece->isBlackCheck())
    {
        std::cout << "Not your turn! Move black pieces now." << std::endl;
        return true;
    }
    
    return false;
}

// inverts the coordinates so that red and black moves can be handled in the same way
void invertCoordinates(int& originRow, int& originCol, int& destRow, int& destCol) {
    destRow = 7 - destRow;
    destCol = 7 - destCol;
    originRow = 7 - originRow;
    originCol = 7 - originCol;
}


// parses the inputted string into 2 pairs of ints. the first pair is the initial row & col, second is the destination row & col
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

            // adjusts the input for the board's handling of coordinates
            int originCol = stringMove[0] - 'a';
            int originrow = stringMove[1] - '1';
            int destCol = stringMove[3] - 'a';
            int destrow = stringMove[4] - '1';

            parsedMoves.push_back({{originrow, originCol}, {destrow, destCol} });
            
        }
     return parsedMoves;
}

void Board::checkPromotion(int originRow, int originCol)
{
    Piece* piece = board[originRow][originCol];
    
    // casting or else could not get the promotion() function to work 
    Checker* checker = dynamic_cast<Checker*>(piece);
    
    
    if (checker != nullptr && checker -> promotion())
    {
        bool colourKeeper;
        bool statusKeeper;
        
        // keep the description of regular checker
        colourKeeper = checker -> isBlackCheck();
        statusKeeper = checker -> isCapturedCheck();
        
        // memory cleanup
        delete checker;
        board[originRow][originCol] = nullptr;
        
        // replacing regular checker with kingChecker
        board[originRow][originCol] = new KingChecker(colourKeeper,statusKeeper, originRow, originCol);
        
        std::cout << "Checker has been promoted to KingChecker" << std::endl;
    }
}
