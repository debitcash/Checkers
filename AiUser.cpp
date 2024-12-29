#include <iostream>
#include "Board.h"
#include "User.h"
#include <vector>

class AiUser : public User
{
    private:
        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >  optimalMove;
        
    public:
        std::string getAiMove(Board originalBoard)
        {
            Board testBoard(originalBoard);
            Piece* (*board)[8] = *testBoard.getBoard();
            
            // super low value for maximising player 
            int alpha = -10000; 
            
            // super high value for minimising player
            int beta = 10000; 
            
            // get the optimal move in the
            miniMaxResult(testBoard, true, 2, alpha, beta);
            
            std::string result;
            
            // create a move in string form
            for (std::pair<std::pair<int, int>, std::pair<int, int> > move : optimalMove)
            {
                result += 'a' + 7 - move.first.second;
                result += '1' + 7 - move.first.first;
                result += '>';
                result += 'a' + 7 - move.second.second;
                result += '1' + 7 - move.second.first;
                result += " ";
            }
            
            // cleanup the board array
            cleanupBoardMemory(board);

            return result;
        }
        
        int miniMaxResult(Board boardOrig, bool isMaxPlayer, int depth, int pruningAlpha, int pruningBeta) // maxplayer== black pieces
        {
            // get value when reached bottom of decision tree
            if (depth == 0)
            {
                return getBlackMinusRed(*boardOrig.getBoard());
            }
            
            depth--;
            
            if (isMaxPlayer)
            {
                // invert, because AI is always black piece player
                boardOrig.invertBoard();
                
                int maxBalance = -100000;
                 
                // all the moves that are available for current color
                std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allMoves = getMovesForCurrentColor(boardOrig, isMaxPlayer);
                
                // check if moves include capture moves, and enforce AI to chose among them
                enforceCaptureMove(allMoves);
                
                // do the moves that are available and get the one that has the best potential value according to minimax algo
                for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >   allPathsForPiece : allMoves)
                {
                    // create copy of the current board
                    Board boardObj(boardOrig);
                    Piece* (*boardCopy)[8] = *boardObj.getBoard();
                    
                    // do the move sequence or single move on the copy, because they both stored in vector
                    for (std::pair<std::pair<int, int>, std::pair<int, int> > move : allPathsForPiece)
                    {
                        movePiece(move, boardCopy);
                    }
                    
                    // the value that stores the position evaluation
                    int newBalance;
                    newBalance = miniMaxResult(boardObj, false, depth, pruningAlpha, pruningBeta);
                    
                    // update the best move coordinates if new move yields better result than previous best
                    if (newBalance >= maxBalance)
                    {
                        maxBalance = newBalance;
                        optimalMove = allPathsForPiece;
                    }
                   
                    // pruning logic
                    int pruningValue = newBalance;
                    if (pruningValue >= pruningBeta)
                        return maxBalance;
                    if (pruningValue > pruningAlpha)
                        pruningAlpha = pruningValue;
                   
                    // cleanup memory
                    cleanupBoardMemory(boardCopy);
                }
                return maxBalance;
            }
            
            else
            {
                
                boardOrig.invertBoard();
                
                int minBalance = 100000;
                
                std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allMoves = getMovesForCurrentColor(boardOrig, isMaxPlayer);
                enforceCaptureMove(allMoves);
                 
                for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >   allPathsForPiece : allMoves)
                {
                    Board boardObj(boardOrig);
                    Piece* (*boardCopy)[8] = *boardObj.getBoard();
                    
                    for (std::pair<std::pair<int, int>, std::pair<int, int> > move : allPathsForPiece)
                    {
                        movePiece(move, boardCopy);
                    }
                        
                    int newBalance;
                    newBalance = miniMaxResult(boardObj, true, depth, pruningAlpha, pruningBeta);
                    
                    if (newBalance <= minBalance)
                    {
                        minBalance = newBalance;
                    }
                    
                    int pruningValue = newBalance;
                    if (pruningValue <= pruningAlpha)
                        return minBalance;
                    if (pruningValue < pruningBeta)
                        pruningBeta = pruningValue;
                    
                    cleanupBoardMemory(boardCopy);
                }
                return minBalance;
            }
        }
        
        // moves the piece on the provided board and cleans up the memory occupied
        void movePiece(std::pair<std::pair<int, int>, std::pair<int, int> >  move, Piece* board [8][8])
        {
            int originRow = move.first.first;
            int originCol = move.first.second; 
            int destRow = move.second.first;
            int destCol = move.second.second;
            
            if (originRow + 2 == destRow)
            {
                delete board[(originRow + destRow) / 2][(originCol + destCol) / 2];
                board[(originRow + destRow) / 2][(originCol + destCol) / 2] = nullptr;
            }
            if (originRow - 2 == destRow)
            {
                delete board[(originRow + destRow) / 2][(originCol + destCol) / 2];
                board[(originRow + destRow) / 2][(originCol + destCol) / 2] = nullptr;
            }
            
            board[destRow][destCol] = board[originRow][originCol];
            board[originRow][originCol] = nullptr;
             
            board[destRow][destCol]->setOriginCol(destCol);
            board[destRow][destCol]->setOriginRow(destRow);
        }
        
        // return current balance on the board as total black pieses minus total red pieces
        int getBlackMinusRed(Piece* board [8][8])
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
        
        // get all possible moves for a color that lead to different states and are valid
        std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > getMovesForCurrentColor(Board boardOrig, bool isMaxPlayer)
        {
            Piece* (*board)[8] = *boardOrig.getBoard();
            
            // stores vectors that contain both single moves and multiple hops
            std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allPossiblePaths;
             
            // iterate through the board and check all possible moves for a piece
            for (int row = 0; row < 8; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    if (board[row][col] != nullptr && (board[row][col]->isBlackCheck() == isMaxPlayer))
                    {
                        // stores the sequence for hopping
                        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > emptySequence;
                        
                        // check if kingchecker
                        bool isKingChecker = typeid(*board[row][col]) == typeid(KingChecker);
                        
                        // check if hops or capture moves are available
                        recursiveHopCheck(row, col, board, isMaxPlayer, emptySequence, allPossiblePaths, isKingChecker);
                        
                        // enforce capturemove, by not including single row moves if captures are available
                        if (allPossiblePaths.size() == 0)
                        {
                            // stores single row move
                            std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > singleRowMove;
                            
                            // stores possible directions of movement
                            std::vector<std::pair<int, int>> directions = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
                            
                            // can move left top and right top only if regular checker
                            int directionTypes = 2;
                            
                            // can move all 4 ways if king checker
                            if (isKingChecker)
                                directionTypes = 4;
                            
                            // check a single row move for each direction
                            for (int i = 0; i < directionTypes; i++) 
                            {
                                if(row + directions[i].first < 8 && row + directions[i].first >= 0 && col + directions[i].second < 8 && col + directions[i].second >= 0
                                    && board[row + directions[i].first][col + directions[i].second] == nullptr)
                                {
                                    singleRowMove.push_back({{row, col}, {row + directions[i].first, col + directions[i].second}});
                                    
                                    allPossiblePaths.push_back(singleRowMove);
                                    singleRowMove.clear();
                                }
                            }
                        }
                    }
                }
            }
            return allPossiblePaths;
        }
        
        // recursively check for all possible hop sequences for a piece
        void recursiveHopCheck(int row, int col, Piece* board [8][8], bool isBlack, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sequence,
                                    std::vector<  std::vector<std::pair<  std::pair<int, int>, std::pair<int, int> > > > &allSequences, bool isKingChecker)
        {
            // when reached the dead end, add the traced path to available sequences 
            if ((sequence.size() > 0) &&
                !(row + 2 < 8 && col + 2 < 8 && (board[row + 1][col + 1] != nullptr && board[row + 1][col + 1]->isBlackCheck() != isBlack) && board[row + 2][col + 2] == nullptr) &&
                !(row + 2 < 8 && col - 2 >= 0 && (board[row + 1][col - 1] != nullptr && board[row + 1][col - 1]->isBlackCheck() != isBlack) && board[row + 2][col - 2] == nullptr)) 
            
            {
                allSequences.push_back(sequence);
                return;
            }
            
            // check and start the top right hop sequence
            if (row + 2 < 8 && col + 2 < 8 && (board[row + 1][col + 1] != nullptr && board[row + 1][col + 1]->isBlackCheck() != isBlack) && board[row + 2][col + 2] == nullptr)
            {
                sequence.push_back({{row,col},{row + 2, col + 2}});
                recursiveHopCheck(row + 2, col + 2, board, isBlack, sequence, allSequences, isKingChecker);
                sequence.pop_back();
            }
            
            // check and start the top left sequence
            if (row + 2 < 8 && col - 2 >= 0 && (board[row + 1][col - 1] != nullptr && board[row + 1][col - 1]->isBlackCheck() != isBlack) && board[row + 2][col - 2] == nullptr)
            {
                sequence.push_back({{row,col},{row + 2, col - 2}});
                recursiveHopCheck(row + 2, col - 2, board, isBlack, sequence, allSequences, isKingChecker);
                sequence.pop_back();
            }
            
            if (isKingChecker)
            {
                // check and start the bottom right sequence
                if (row - 2 >= 0 && col - 2 >= 0 && (board[row - 1][col - 1] != nullptr && board[row - 1][col - 1]->isBlackCheck() != isBlack) && board[row - 2][col - 2] == nullptr)
                {
                    sequence.push_back({{row,col},{row - 2, col - 2}});
                    recursiveHopCheck(row - 2, col - 2, board, isBlack, sequence, allSequences, isKingChecker);
                    sequence.pop_back();
                }
            
                // check and start the bottom left sequence
                if (row - 2 >= 0 && col + 2 < 8 && (board[row - 1][col + 1] != nullptr && board[row - 1][col + 1]->isBlackCheck() != isBlack) && board[row - 2][col + 2] == nullptr)
                {
                    sequence.push_back({{row,col},{row - 2, col + 2}});
                    recursiveHopCheck(row - 2, col + 2, board, isBlack, sequence, allSequences, isKingChecker);
                    sequence.pop_back();
                }
            }
        }
        
        // service method to clear the memory on heap from the pieces on the board
        void cleanupBoardMemory(Piece* board [8][8])
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
        
        // service method for debugging
        void display(Piece* board [8][8])
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

        // enforces capture moves, by removing single row moves
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
    
};
