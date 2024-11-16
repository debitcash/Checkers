#include "Board.cpp"
#include "Checker.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265

int main(){

	//consider having player enter moves individually (specifically for double jump/ triple jump moves) this
	//would make it so that board and piece class only have to consider cases of single moves, and just get multiple
	//of them in a row

	Board board;

    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();
    //board.newMove(1, 0, 2, 0, turn)
	//
	// bool stalemate = false, checkmate = false;
 //
 //    while (!checkmate || !stalemate)
 //    {
 //        int originRow, originCol, destRow, destCol;
 //
 //        std::cout << std::endl << "Provide the move in a form [originRow originCol destRow destCol.]" << std::endl;
 //        std::cin >> originRow >> originCol >> destRow >> destCol ;
 //
 //        board.move(originRow, originCol, destRow, destCol, turn);
 //
 //    }
 //

    return 0;
}
