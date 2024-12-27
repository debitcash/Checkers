#include <iostream>
#include "Board.h"
#include "User.h"
#include <vector>

class AiUser : public User
{

    
    public:
        std::string getAiMove(Board originalBoard)
        {
            Board testBoard(originalBoard);
            Piece* (*board)[8] = *testBoard.getBoard();
            

            
            std::pair< std::pair<int, int>, std::pair<int, int>  > move = miniMaxResult(testBoard, true, 2);
            
            std::string result;
            
            result += 'a' + 7 - move.first.second;
            result += '1' + 7 - move.first.first;
            result += '>';
            result += 'a' + 7 - move.second.second;
            result += '1' + 7 - move.second.first;
            
            
            //std::string result = originRow + " " + originCol + ">" + destRow + " "+ destCol;
            
            //std::cout << "===============" << " " << result;
            cleanupBoardMemory(board);


            return result;
            
        }
        
        std::pair< std::pair<int, int>, std::pair<int, int>  > miniMaxResult(/*int row, int column, Piece* board [8][8],*/Board boardOrig, bool isMaxPlayer, int depth) // maxplayer== black pieces
        {
            depth--;
            
            //std::cout << "DEPTH IS" << depth <<std::endl;
            
            if (isMaxPlayer)
            {
                boardOrig.invertBoard();
                
                //1INvert?
                 
                int maxBalance = -100000;
                std::pair<std::pair <int, int>, std::pair <int, int> > maxMove;
                
                Piece* (*board)[8] = *boardOrig.getBoard();
                
                
                
                for (std::pair<std::pair<int, int>, std::pair<int, int> >  move : getMovesForCurrentColor(board, isMaxPlayer))
                {
                    Board boardObj(boardOrig);
                    Piece* (*boardCopy)[8] = *boardObj.getBoard();
                    
                    //display(boardCopy);
                    
                    int newBalance;
                    std::pair<std::pair<int, int>, std::pair<int, int> > nextChosenMove ;
                    
                    
                    
                    if (depth == 0)
                    {
                        //std::cout << "I am here!" << std::endl;
                        
                        std::cout << move.first.first << move.first.second << " to " << move.second.first << move.second.second << std::endl;
                        
                        nextChosenMove = move;
                        
                        
                        newBalance = getBlackMinusRed(move, boardCopy);
                        //std::cout << "After move"<< std::endl;
                    }
                    
                    else
                    {
                        
                        movePiece(move.first.first, move.first.second, move.second.first, move.second.second, boardCopy);
                        
                        nextChosenMove = miniMaxResult(boardObj, !isMaxPlayer, depth);
                        
                        boardObj.invertBoard();
                        newBalance = getBlackMinusRed(nextChosenMove, boardCopy);
                        //std::cout<< "BALANCE IS: " << newBalance << std::endl;
                        
                    }
                    
                    if (newBalance >= maxBalance)
                    {
                        
                        //std::cout << newBalance << maxBalance << "COMPARING===" << (newBalance >= maxBalance) << std::endl;
                        
                        //std::cout << "BALANCE WAS CHANGED-=====================" << std::endl;
                        maxBalance = newBalance;
                        maxMove = move;
                    }
                   
                    
                    cleanupBoardMemory(boardCopy);
                    
                    
                }
                std::cout << "Max result is!" << maxMove.first.first << maxMove.first.second << " " << maxMove.second.first << maxMove.second.second << std::endl;
                return maxMove;
            }
            
            else
            {
                boardOrig.invertBoard();
                
                //std::cout << "PAST HERE" << std::endl;
                
                
                int minBalance = 100000;
                std::pair<std::pair <int, int>, std::pair <int, int> > minMove;
                
                Piece* (*board)[8] = *boardOrig.getBoard();
                
                //display(board);
                
                for (std::pair<std::pair<int, int>, std::pair<int, int> >  move : getMovesForCurrentColor(board, isMaxPlayer))// maxplayer already negated
                {
                    Board boardObj(boardOrig);
                    Piece* (*boardCopy)[8] = *boardObj.getBoard();
                    
                    int newBalance;
                    std::pair<std::pair<int, int>, std::pair<int, int> > nextChosenMove ;
                    
                   
                    if (depth == 0)
                    {
                        nextChosenMove = move;
                        newBalance = getBlackMinusRed(move, boardCopy);
                    }
                    
                    else
                    {
                        movePiece(move.first.first, move.first.second, move.second.first, move.second.second, boardCopy);
                        nextChosenMove = miniMaxResult(boardObj, isMaxPlayer, depth);
                        newBalance = getBlackMinusRed(nextChosenMove, boardCopy);
                    }
                    
                    if (newBalance <= minBalance)
                    {
                        minBalance = newBalance;
                        minMove = nextChosenMove;
                    }
                    
                    cleanupBoardMemory(boardCopy);
                    
                    
                }
                //std::cout << "Minmax result is!" << minMove.first.first << minMove.first.second << " " << minMove.second.first << minMove.second.second << std::endl;
                return minMove;
            }
        }
        
        void movePiece(int originRow, int originCol, int destRow, int destCol, Piece* board [8][8])
        {
            
            if (originRow + 2 == destRow)
            {
                delete board[(originRow + destRow) / 2][(originCol + destCol) / 2];
                board[(originRow + destRow) / 2][(originCol + destCol) / 2] = nullptr;
            }
            
            //std::cout << "After if!" <<std::endl;
            
            
            
            // provide new location for the moved checker
            board[destRow][destCol] = board[originRow][originCol];
            board[originRow][originCol] = nullptr;
            
            //std::cout << "After nullptr" <<std::endl;
            
            //display(board);
            //std::cout << "Moving: " << originRow<<originCol << " " << destRow << destCol << std::endl; 
            
            
            // provide the new coordinates for a piece
            //std::cout << "XXXXXX" <<  (board[destRow][destCol] == nullptr) << std::endl;
            
             
            board[destRow][destCol]->setOriginCol(destCol);
            board[destRow][destCol]->setOriginRow(destRow);
            //std::cout << "After setting" <<std::endl;
        }
        
        
        int getBlackMinusRed(std::pair<std::pair<int, int>, std::pair<int, int> > move, Piece* board [8][8])
        {
            int balance = 0;
            
            //std::cout << "Attempting move" << std::endl;
            movePiece(move.first.first, move.first.second, move.second.first, move.second.second, board);
            //std::cout << "After move"<< std::endl;
            //std::cout << "============AYOOOOOOO=====" << std::endl;
            
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

        std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > getMovesForCurrentColor(Piece* board[8][8], bool isMaxPlayer)
        {
            
            std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > movesAndDestinations;
             
             int count = 0;
             
            for (int row = 0; row < 8; row++)
            {
                for (int col = 0; col < 8; col++)
                {
                    if (board[row][col] != nullptr && (board[row][col]->isBlackCheck() == isMaxPlayer)) // check all pieces of the current color
                    {
                        //std::cout << "Found: " << ++count << std::endl;
                        
                        if (row + 1 < 8 && col + 1 < 8 && board[row + 1][col + 1] == nullptr)
                            movesAndDestinations.push_back({{row,col},{row + 1, col + 1}});
                            
                        if (row + 1 < 8 && col - 1 >= 0 && board[row + 1][col - 1] == nullptr)
                            movesAndDestinations.push_back({{row,col},{row + 1, col - 1}});
                            
                        if (row + 2 < 8 && col + 2 < 8 && (board[row + 1][col + 1] != nullptr && board[row + 1][col + 1]->isBlackCheck() != board[row][col]->isBlackCheck()) && board[row + 2][col + 2] == nullptr)
                            movesAndDestinations.push_back({{row,col},{row + 2, col + 2}});
             
                        if (row + 2 < 8 && col - 2 >= 0 && (board[row + 1][col - 1] != nullptr && board[row + 1][col - 1]->isBlackCheck() != board[row][col]->isBlackCheck()) && board[row + 2][col - 2] == nullptr)
                            movesAndDestinations.push_back({{row,col},{row + 2, col - 2}});
                    }
                }
            }
            
            return movesAndDestinations;
        }

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
};
