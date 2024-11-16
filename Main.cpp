#include "Board.cpp"
/*#include "Checker.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265*/

std::pair<std::pair<int, int>, std::pair<int, int>> parseMove(const std::string& move);

int main(){

	//consider having player enter moves individually (specifically for double jump/ triple jump moves) this
	//would make it so that board and piece class only have to consider cases of single moves, and just get multiple
	//of them in a row

	Board board;

    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();

	bool cont = true;


	while(cont) {
		int originRow, destRow;
		char originCol, destCol;

		std::string input;

		std::cout << std::endl << "Provide a move in the form originRow+originCol>destRow+destCol\n\teg. b3>c4" << std::endl;
		std::cin >> input;

		auto result = parseMove(input);

		//std::cout << originCol << originRow << destCol << destRow;
		board.move(result.first.first, result.first.second, result.second.first, result.second.second, turn);
		turn++;

		//board.display();
	}
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

    return 0;
}

std::pair<std::pair<int, int>, std::pair<int, int>> parseMove(const std::string& move) {
	if(move.size() != 5 || move[2] != '>') {
		return std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
	}

	int originCol = move[0] - 'a';
	int originrow = move[1] - '1';
	int destCol = move[3] - 'a';
	int destrow = move[4] - '1';

	return {{originrow, originCol}, {destrow, destCol} };
}
