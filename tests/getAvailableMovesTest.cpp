#include "../src/Piece.h"
#include "../src/Board.h"
#include "../src/Checker.h"
#include "../src/KingChecker.h"

int main()
{
    Board testBoard;
    
    // populate board with 1 red checker and 1 red kingchecker 
    Piece* (*boardArray)[8] = testBoard.getBoard();

    boardArray[1][1] = new Checker(false, false, 1, 1, false);
    boardArray[3][5] = new KingChecker(false, false, 0, 1);
    
    // populate with black pieces to be captured
    boardArray[2][2] = new Checker(true, false, 7 - 7, 7 - 0, false);
    boardArray[4][6] = new KingChecker(true, false, 7 - 7, 7 - 6);
    boardArray[6][6] = new KingChecker(true, false, 7 - 7, 7 - 6);
    
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > moves;
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > correctMoves;
    
    // populate the correct moves with such
    correctMoves.push_back({{{1,1},{2,0}}});
    correctMoves.push_back({{{1,1},{3,3}}});
    correctMoves.push_back({{{3,5},{4,4}}});
    correctMoves.push_back({{{3,5},{2,4}}});
    correctMoves.push_back({{{3,5},{2,6}}});
    correctMoves.push_back({{{3,5},{5,7}},{{5,7},{7,5}}});

    // find all moves for red pieces
    moves = testBoard.getAvailableMovesForColor(false);
    testBoard.cleanupBoardMemory();
    
    // check if all moves found do match the correct moves
    for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > move : moves)
    {
        if (move == correctMoves[0] || move == correctMoves[1] || move == correctMoves[2] || move == correctMoves[3] || move == correctMoves[4] || move == correctMoves[5])
        {
            std::cout << "Matched" << std::endl;
        }
        
        else
        {
            std::cout << "Failed the match" << std::endl;
            return 1;
        }
    }
    
    return 0;
}
