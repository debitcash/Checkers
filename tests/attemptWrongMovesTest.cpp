#include "../src/Piece.h"
#include "../src/Board.h"
#include "../src/Checker.h"
#include "../src/KingChecker.h"

int main()
{
    Board testBoard;
    
    // populate board with 1 red checker and 1 red kingchecker 
    
    Piece* (*boardArray)[8] = testBoard.getBoard();
    
    // color captured promotionstatus
    boardArray[0][1] = new Checker(false, false, 0, 1, false);
    boardArray[0][4] = new KingChecker(false, false, 0, 5);
    boardArray[7][7] = new Checker(false, false, 7, 7, false);
    
    boardArray[1][2] = new KingChecker(true, false, 7 - 1, 7 - 2);
    boardArray[1][3] = new KingChecker(true, false, 7 - 1, 7 - 3);
    
    int redTurn = 0;
    
    // try move empty space
    testBoard.attemptMove("a1>b2", redTurn);
    bool emptyMoveExecuted = redTurn != 0;
    
    // try move in wrong turn
    testBoard.attemptMove("b1>a2", redTurn);
    bool wrongTurnMoveExecuted = redTurn != 0;
    
    // try move outside the board
    testBoard.attemptMove("h8>g9", redTurn);
    bool outBondsMoveExecuted = redTurn != 0;

    testBoard.cleanupBoardMemory();

    return outBondsMoveExecuted && wrongTurnMoveExecuted && emptyMoveExecuted;
}
