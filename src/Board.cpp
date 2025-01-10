#include <vector>
#include <sstream>
#include <typeinfo>
#include <iostream>
#include "Board.h"

// class that is responsible for all the piece movements on the board, and visually displaying the game

// allows for colour usability
// #include <windows.h>

void invertCoordinates(int& originRow, int& originCol, int& destRow, int& destCol);

// parses string coordinates into a vector of int pairs
std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > parseMove(const std::string& moves);

Board::Board(){}

// initialise the board with general checker layout
void Board::initialise()
{
    Piece* newBoard[8][8] = {
        {nullptr, new Checker(false, false, 0, 1,false), nullptr, new Checker(false, false, 0, 3,false),
            nullptr, new Checker(false, false, 0, 5,false), nullptr, new Checker(false, false, 0, 7,false)}, // red pieces
        {new Checker(false, false, 1, 0,false), nullptr, new Checker(false, false, 1, 2,false), nullptr,
            new Checker(false, false, 1, 4,false), nullptr, new Checker(false, false, 1, 6,false), nullptr},
        {nullptr, new Checker(false, false, 2, 1,false), nullptr, new Checker(false, false, 2, 3,false),
            nullptr, new Checker(false, false, 2, 5,false), nullptr, new Checker(false, false, 2, 7,false)},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {new Checker(true, false, 7 - 5, 7 - 0, false), nullptr, new Checker(true, false, 7 - 5, 7 - 2, false), nullptr,
            new Checker(true, false, 7 - 5, 7 - 4, false), nullptr, new Checker(true, false, 7 - 5, 7 - 6, false), nullptr},
        {nullptr, new Checker(true, false, 7 - 6, 7 - 1, false), nullptr, new Checker(true, false, 7 - 6, 7 - 3, false), nullptr,
            new Checker(true, false, 7 - 6, 7 - 5, false), nullptr, new Checker(true, false, 7 - 6, 7 - 7, false)},
        {new Checker(true, false, 7 - 7, 7 - 0, false), nullptr, new Checker(true, false, 7 - 7, 7 - 2, false), nullptr,
            new Checker(true, false, 7 - 7, 7 - 4, false), nullptr, new Checker(true, false, 7 - 7, 7 - 6, false), nullptr}};
            
    // reassign the default board with general checker layout
    for (int row = 0; row < 8; row++) 
    {
        for (int col = 0; col < 8; col++) 
        {
            board[row][col] = newBoard[row][col];
        }
    }
}

// deep copy constructor
Board::Board(Board &originalBoard)
{
    // populate with the same values as in the targeted board
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            if (originalBoard.board[row][column] != nullptr)
            {
                Piece* piece = originalBoard.board[row][column];
                
                // account for different checker types
                if (typeid(*piece) == typeid(Checker))
                {
                    Checker* oldCheckerPtr = dynamic_cast<Checker *>(piece);
                    Checker* newCheckerPtr = new Checker(*oldCheckerPtr);
                    board[row][column] = newCheckerPtr;
                }
                else
                {
                    KingChecker* oldCheckerPtr = dynamic_cast<KingChecker *>(piece);
                    KingChecker* newCheckerPtr = new KingChecker(*oldCheckerPtr);
                    board[row][column] = newCheckerPtr;
                } 
            }
        }
    }
}

// attempt to make a move with user-provided coordinates
void Board::attemptMove(std::string input, int& turn)
{
    bool isBlack = turn % 2 == 0;
    
    // store the user-provided moves, converted from string to coordinates by parse function. Can be either 1 move, or multiple hops
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > providedMove = parseMove(input);
    
    // invert the board and provided coordinates for black piece player
    if (isBlack)
    {
        invertBoard();
        
        for (std::pair<std::pair<int, int>, std::pair<int, int> > &move : providedMove)
        {
            invertCoordinates(move.first.first, move.first.second, move.second.first, move.second.second);
        }
    }

    // store all the available moves for a current color
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allAvailableMoves = getAvailableMovesForColor(isBlack);
    
    // move the piece if user-provided move matches any move in all available moves
    for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > availableMove : allAvailableMoves)
    {
        if (availableMove == providedMove)
        {
            for (std::pair<std::pair<int, int>, std::pair<int, int> > move : availableMove)
            {
                this->movePiece(move);
            }
            
            isBlack ? this->invertBoard() : void();
            
            turn++;
            
            return;
        }
    }
    
    isBlack ? this->invertBoard() : void();
    
    std::cout << "The move you provided is not valid, please try again." <<std::endl;
        return;

}

// get all the available moves based on current board state for a certain piece color
std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > Board::getAvailableMovesForColor(bool isBlack)
{
    // stores vectors that contain both single moves and multiple hops
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > availableMoves;
    
    // iterate through the board and check all possible moves for a piece
    for (int row = 0; row < 8; row++)
    {
        for (int col = 0; col < 8; col++)
        {
            if (board[row][col] != nullptr && (board[row][col]->isBlackCheck() == isBlack))
            {
                // stores the sequence for hopping
                std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > hopSequence;
                
                // check if kingchecker
                bool isKingChecker = typeid(*board[row][col]) == typeid(KingChecker);
                
                // check if hops or capture moves are available
                findHopPaths(row, col, isBlack, hopSequence, availableMoves, isKingChecker);
                
                // stores single row move
                std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > singleRowMove;
                
                // stores possible directions of movement
                std::vector<std::pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
                
                // can move left top and right top only if regular checker
                int directionTypes = isKingChecker ? 4 : 2;
                
                // check a single row move for each direction
                for (int i = 0; i < directionTypes; i++) 
                {
                    if(row + directions[i].first < 8 && row + directions[i].first >= 0 && col + directions[i].second < 8 && col + directions[i].second >= 0
                        && board[row + directions[i].first][col + directions[i].second] == nullptr)
                    {
                        singleRowMove.push_back({{row, col}, {row + directions[i].first, col + directions[i].second}});
                        
                        availableMoves.push_back(singleRowMove);
                        singleRowMove.clear();
                    }
                }
            }
        }
    }

    return availableMoves;
}

// service methods that provides hop moves to getAvailableMovesForColor method
void Board::findHopPaths(int row, int col, bool isBlack, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sequence,
                                    std::vector<  std::vector<std::pair<  std::pair<int, int>, std::pair<int, int> > > > &allSequences, bool isKingChecker)
{ 
    // move validity checks
    bool topRightHopIsValid = row + 2 < 8 && col - 2 >= 0 && (board[row + 1][col - 1] != nullptr && board[row + 1][col - 1]->isBlackCheck() != isBlack) && board[row + 2][col - 2] == nullptr;
    bool topLeftHopIsValid = row + 2 < 8 && col + 2 < 8 && (board[row + 1][col + 1] != nullptr && board[row + 1][col + 1]->isBlackCheck() != isBlack) && board[row + 2][col + 2] == nullptr;
    bool bottomRightHopIsValid = false;
    bool bottomLeftHopIsValid = false;
    
    // account for backhopping
    if (isKingChecker)
    {
        bool backToTopRight = false;
        bool backToTopLeft = false;
        bool backToBottomRight = false;
        bool backToBottomLeft = false;
        
        // ban returning options, otherwise will lead to circular infinite loops from the path
        if (!sequence.empty())
        {
            std::pair<int, int> previousLocation = sequence.back().first;
            
            backToTopRight = (previousLocation.first == row + 2) && (previousLocation.second == col - 2);
            backToTopLeft = (previousLocation.first == row + 2) && (previousLocation.second == col + 2);
            
            backToBottomRight = (previousLocation.first == row - 2) && (previousLocation.second == col - 2);
            backToBottomLeft = (previousLocation.first == row - 2) && (previousLocation.second == col + 2);
        }
        
        topRightHopIsValid = topRightHopIsValid && !backToTopRight;
                    
        topLeftHopIsValid = topLeftHopIsValid && !backToTopLeft;
        
        bottomRightHopIsValid = row - 2 >= 0 && col - 2 >= 0 && (board[row - 1][col - 1] != nullptr && board[row - 1][col - 1]->isBlackCheck() != isBlack) 
                    && board[row - 2][col - 2] == nullptr && !backToBottomRight;
                    
        bottomLeftHopIsValid = row - 2 >= 0 && col + 2 < 8 && (board[row - 1][col + 1] != nullptr && board[row - 1][col + 1]->isBlackCheck() != isBlack) 
                    && board[row - 2][col + 2] == nullptr && !backToBottomLeft;
    }
    
    // when reached the dead end, add the traced path to available sequences 
    if (sequence.size() > 0 && !topLeftHopIsValid && !topRightHopIsValid && !bottomLeftHopIsValid && !bottomRightHopIsValid)
    {
        allSequences.push_back(sequence);
        return;
    }
    
    // possible piece moves relative to current position
    std::vector<std::pair<int, int > > hopVectors = {{2, -2}, {2, 2}, {-2, 2}, {-2, -2}};
    
    // account for backwards movement of king checker
    int vectorsToCheck = isKingChecker ? 4 : 2;
    
    std::vector<bool> hopValidity = {topRightHopIsValid, topLeftHopIsValid, bottomLeftHopIsValid, bottomRightHopIsValid};
    
    // add current hop to hop sequence path
    for (int i = 0; i < vectorsToCheck; i++)
    {
        if (hopValidity[i] == true)
        {
            sequence.push_back({{row,col},{row + hopVectors[i].first, col + hopVectors[i].second}});
            findHopPaths(row + hopVectors[i].first, col + hopVectors[i].second, isBlack, sequence, allSequences, isKingChecker);
            sequence.pop_back();
        }
    }
}

// move the piece and updates the board 
void Board::movePiece(std::pair<std::pair<int, int>, std::pair<int, int> >  move)
{
    int originRow = move.first.first;
    int originCol = move.first.second; 
    int destRow = move.second.first;
    int destCol = move.second.second;
    
    // delete the captured piece
    if (originRow + 2 == destRow || originRow - 2 == destRow)
    {
        delete board[(originRow + destRow) / 2][(originCol + destCol) / 2];
        board[(originRow + destRow) / 2][(originCol + destCol) / 2] = nullptr;
    }
    
    // reassign the pointer
    board[destRow][destCol] = board[originRow][originCol];
    board[originRow][originCol] = nullptr;
    
    // cleanup the memory after the old location
    board[destRow][destCol]->setOriginCol(destCol);
    board[destRow][destCol]->setOriginRow(destRow);
    
    checkPromotion(destRow,destCol);
}

// clear the heap memory, occupied by the board
void Board::cleanupBoardMemory()
{
    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            if (board[row][column] != nullptr)
            {
                delete board[row][column];
                board[row][column] = nullptr;
            }
        }
    }
}

// inverts the coordinates so that red and black moves can be handled in the same way
void invertCoordinates(int& originRow, int& originCol, int& destRow, int& destCol) {
    destRow = 7 - destRow;
    destCol = 7 - destCol;
    originRow = 7 - originRow;
    originCol = 7 - originCol;
}

// inverts the board so that red and black pieces can be handled the same way
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

// display the default style of the board in terminal
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
            //if the piece is black
            else if (board[y][x]->isBlackCheck())
            {
                if(typeid(*board[y][x]) == typeid(KingChecker)) {
                    std::cout << "B ";
                }else {
                    std::cout << "b ";
                }
            }
            //if the piece is red
            else if (!board[y][x]->isBlackCheck())
            {
                if(typeid(*board[y][x]) == typeid(KingChecker)) {
                    std::cout << "R ";
                }else {
                    std::cout << "r ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--+-----------------" << std::endl;
    std::cout << "  | a b c d e f g h" << std::endl;
    }
         
/*
// display the board in color in terminal
void Board::display() const
{
    ///allows for colour printout in the terminal
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
            //if the piece is black
            else if (board[y][x]->isBlackCheck())
            {
                if(typeid(*board[y][x]) == typeid(KingChecker)) {
                    std::cout << "\033[34m\u265B\033[0m ";
                }else {
                    std::cout << "\033[34m\u25CF\033[0m ";
                }
            }
            //if the piece is red
            else if (!board[y][x]->isBlackCheck())
            {
                if(typeid(*board[y][x]) == typeid(KingChecker)) {
                    std::cout << "\033[31m\u265B\033[0m ";
                }else {
                    std::cout << "\033[31m\u25CF\033[0m ";
                }
            }
        }
        std::cout << std::endl;
    }
    std::cout << "--+-----------------" << std::endl;
    std::cout << "  | a b c d e f g h" << std::endl;
}*/

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

// promote a checker to king checker
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
        
        //std::cout << "Checker has been promoted to KingChecker" << std::endl;
    }
}

// get the difference between black and red pieces
int Board::getBlackMinusRed()
{
    int balance = 0;

    for (int row = 0; row < 8; row++)
    {
        for (int column = 0; column < 8; column++)
        {
            if (board[row][column] != nullptr && board[row][column]->isBlackCheck())
            {
                balance += 1;
            }
            else if (board[row][column] != nullptr && !board[row][column]->isBlackCheck())
            {
                balance -= 1;
            }
        }
    }
    return balance;
}

// service method, deletes the single row moves from all available moves, if capture moves are available
// this makes capture moves unavoidable
void enforceCaptureMove(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > &allMoves)
{
    bool captureMovePresent = false;
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > newMoves;
    
    // if capturemove is found in population of moves, raise the flag that capture moves should be enforced
    for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > move : allMoves)
    {
        if (move.size() > 1 || move[0].first.first + 2 == move[0].second.first || move[0].first.first - 2 == move[0].second.first)
        {
            captureMovePresent = true;
            break;
        }
    }
    
    // if capture move flag is raised
    if (captureMovePresent)
    {
        // select only the capture moves as available moves, even though single rows are also possible
        for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > move : allMoves)
        {   
            if (move.size() > 1 || move[0].first.first + 2 == move[0].second.first || move[0].first.first - 2 == move[0].second.first)
            {
                newMoves.push_back(move);
            }
        }
        allMoves = newMoves;
    }
}
