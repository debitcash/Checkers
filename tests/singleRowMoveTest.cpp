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
    
    boardArray[7][0] = new Checker(true, false, 7 - 7, 7 - 0, false);
    boardArray[7][6] = new KingChecker(true, false, 7 - 7, 7 - 6);
    
    testBoard.display();
    
    int blackTurn = 1;
    int redTurn = 0;
    
    // move regular red checker left and right
    testBoard.attemptMove("b2>c3", --redTurn);
    testBoard.attemptMove("c3>b4", --redTurn);
    // move red king checker left and right
    testBoard.attemptMove("f4>g5", --redTurn);
    testBoard.attemptMove("g5>f6", --redTurn);
    
    // move regular black checker left and right
    testBoard.attemptMove("a8>b7", --blackTurn);
    testBoard.attemptMove("b7>a6", --blackTurn);
    // move black king checker left and right
    testBoard.attemptMove("g8>h7", --blackTurn);
    testBoard.attemptMove("h7>g6", --blackTurn);
    
    // check red king checker backward movements
    testBoard.attemptMove("f6>g5", --redTurn);
    testBoard.attemptMove("g5>f4", --redTurn);
    testBoard.attemptMove("f4>g3", --redTurn);
    
    // check black king checker backward movements
    testBoard.attemptMove("g6>h7", --blackTurn);
    testBoard.attemptMove("h7>g8", --blackTurn);
    testBoard.attemptMove("g8>f7", --blackTurn);
    
    // check if the location of checkers are correct
    bool correctLastPosition = boardArray[2][6] != nullptr && boardArray[3][1] != nullptr &&
        boardArray[5][0] != nullptr && boardArray[6][5] != nullptr;
    
    // check if the coordinates were cleaned up after the moves
    bool cleanupDone = boardArray[1][1] == nullptr && boardArray[3][5] == nullptr &&
        boardArray[7][0] == nullptr && boardArray[7][6] == nullptr;
        
    testBoard.cleanupBoardMemory();
    
    // flip the boolean value, as far as return 1 represents the failed test in CMake
    return !correctLastPosition && !cleanupDone;
}
