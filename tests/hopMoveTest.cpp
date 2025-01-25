#include "../src/Piece.h"
#include "../src/Board.h"
#include "../src/Checker.h"
#include "../src/KingChecker.h"

int main()
{
    Board testBoard;
    
    Piece* (*boardArray)[8] = testBoard.getBoard();
    
    // populate board with 2 red checkers and 2 black checkers
    boardArray[0][1] = new Checker(false, false, 0, 1, false);
    boardArray[0][4] = new KingChecker(false, false, 0, 5);
    boardArray[1][2] = new KingChecker(true, false, 7 - 1, 7 - 2);
    boardArray[1][3] = new KingChecker(true, false, 7 - 1, 7 - 3);

    int redTurn = 1;
    
    // hop in one direction
    testBoard.attemptMove("b1>d3", redTurn);
    testBoard.attemptMove("e1>c3", --redTurn);

    // hop in other direction
    boardArray[3][3] = new KingChecker(true, false, 7 - 3, 7 - 3);
    boardArray[3][2] = new KingChecker(true, false, 7 - 3, 7 - 2);
    
    // hop in one direction
    testBoard.attemptMove("d3>b5", --redTurn);
    testBoard.attemptMove("c3>e5", --redTurn);
    
    boardArray[3][5] = new KingChecker(true, false, 7 - 3, 7 - 5);
    
    // test hop back right for the king checker 
    testBoard.attemptMove("e5>g3", --redTurn);
    
    boardArray[1][5] = new KingChecker(true, false, 7 - 1, 7 - 5);
    
    // test hop back left for the king checker 
    testBoard.attemptMove("g3>e1", --redTurn);
    
    // check if the 
    bool correctLastPosition = boardArray[4][1] != nullptr && boardArray[0][4] != nullptr;
    
    // check if all the caaptured pieces are removed from the board
    bool cleanupDone = boardArray[1][2] == nullptr && boardArray[1][3] == nullptr &&
        boardArray[3][2] == nullptr && boardArray[3][3] == nullptr &&
        boardArray[3][5] == nullptr && boardArray[1][5] == nullptr;
    
    testBoard.cleanupBoardMemory();
    
    return !correctLastPosition && !cleanupDone;
}
