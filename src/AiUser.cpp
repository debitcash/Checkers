#include "AiUser.h"

AiUser::AiUser()
{
    setName("AI player");
}

// get the move, following minimax algorithm
std::string AiUser::getMove(Board originalBoard)
{
    Board testBoard(originalBoard);
    
    // super low value for maximising player 
    int alpha = -10000; 
    
    // super high value for minimising player
    int beta = 10000; 
    
    // initialise max depth for minimax discovery
    maxDepth = 4;
    
    // get the best possible move currently from the board 
    miniMaxResult(testBoard, true, maxDepth, alpha, beta); // insert 1 instead, to make it a regular greedy algorithm
    
    std::string result;
    
    // transform a move in string form
    for (std::pair<std::pair<int, int>, std::pair<int, int> > move : optimalMove)
    {
        // number 7 is used for inverting coordinates, as far as black pieces are always on flipped board
        // and AI is always using black pieces
        result += 'a' + 7 - move.first.second;
        result += '1' + 7 - move.first.first;
        result += '>';
        result += 'a' + 7 - move.second.second;
        result += '1' + 7 - move.second.first;
        result += " ";
    }
    
    // cleanup the board array
    testBoard.cleanupBoardMemory();
    
    result = (result == "" ? "Give up" : result);
    
    std::cout << "AI move: " << result << std::endl;
    
    return result;
}

int AiUser::miniMaxResult(Board boardOrig, bool isMaxPlayer, int depth, int pruningAlpha, int pruningBeta) // maxplayer== black pieces
{
    // get value when reached bottom of decision tree
    if (depth == 0)
    {
        return boardOrig.getBlackMinusRed();
    }
    
    depth--;
    
    // minimax max portion
    if (isMaxPlayer)
    {
        // invert, because AI is always black piece player
        boardOrig.invertBoard();
        
        int maxBalance = -100000;
                
        // all the moves that are available for current color
        std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allMoves = boardOrig.getAvailableMovesForColor(isMaxPlayer);

        // check if moves include capture moves, and enforce AI to chose among them
        enforceCaptureMove(allMoves);
        
        // do the moves that are available and get the one that has the best potential value according to minimax algo
        for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >   allPathsForPiece : allMoves)
        {
            // create copy of the current board
            Board boardObj(boardOrig);
            
            // do the move sequence or single move on the copied board; used for loop because they both stored in vector
            for (std::pair<std::pair<int, int>, std::pair<int, int> > move : allPathsForPiece)
            {
                boardObj.movePiece(move);
            }
            
            // the value that stores the position evaluation
            int newBalance;
            
            newBalance = miniMaxResult(boardObj, false, depth, pruningAlpha, pruningBeta);
            
            // update the best move coordinates if new move yields better result than previous best
            if (newBalance > maxBalance)
            {
                maxBalance = newBalance;
                if (depth == maxDepth - 1)
                    optimalMove = allPathsForPiece;
            }
           
            // cleanup memory
            boardObj.cleanupBoardMemory();
            
            // pruning logic
            pruningAlpha = pruningAlpha > maxBalance ? pruningAlpha : maxBalance;
            
            if (pruningBeta <= pruningAlpha)
            {
                return pruningAlpha;
            }
        }
        return maxBalance;
    }
    
    // minimax min portion
    else
    {
        boardOrig.invertBoard();
        
        int minBalance = 100000;
        
        std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > allMoves = boardOrig.getAvailableMovesForColor(isMaxPlayer);
        
        enforceCaptureMove(allMoves);
        
        for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >   allPathsForPiece : allMoves)
        {
            
            Board boardObj(boardOrig);
            
            for (std::pair<std::pair<int, int>, std::pair<int, int> > move : allPathsForPiece)
            {
                boardObj.movePiece(move);

            }
            
            int newBalance;
            newBalance = miniMaxResult(boardObj, true, depth, pruningAlpha, pruningBeta);
            
            
            if (newBalance < minBalance)
            {
                minBalance = newBalance;
            }
            
            boardObj.cleanupBoardMemory();
            
            pruningBeta = pruningBeta < minBalance ? pruningBeta : minBalance;
            
            if (pruningBeta <= pruningAlpha)
            {
                return pruningBeta;
            }
        }
        return minBalance;
    }
}
