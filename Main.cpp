#include "Board.h"
#include "Checker.h"
#include "Piece.h"
/*#include "Checker.h"

#include <stdio.h>
#include <math.h>

#define PI 3.14159265*/

//parses a string into 2 pairs of ints
std::pair<std::pair<int, int>, std::pair<int, int> > parseMove(const std::string& move);

int main(){

	//consider having player enter moves individually (specifically for double jump/ triple jump moves) this
	//would make it so that board and piece class only have to consider cases of single moves, and just get multiple
	//of them in a row

	Board board;

    // start with red(red - odd, black - even)
    // red at bottom black at top
    int turn = 1; 
    
    board.display();

	bool cont = true;

	while(cont) {
		int originRow, destRow;
		char originCol, destCol;

		std::string color = "Black";
		std::string input;

		if(turn % 2 == 0) {
			color = "Red";
		}

		std::cout << color << "'s turn." << std::endl;
		std::cout << "Provide a move in the form row+col>row+col\n\teg. b3>c4" << std::endl;
		std::cin >> input;

		auto result = parseMove(input);

		//std::cout << originCol << originRow << destCol << destRow;
		board.move(result.first.first, result.first.second, result.second.first, result.second.second, turn);
	}

    return 0;
}

//parses the inputed string into 2 pairs of ints. the first pair is the intial row & col, second is the destination row & col
std::pair<std::pair<int, int>, std::pair<int, int> > parseMove(const std::string& move) {

	//if the entered string is not the right length or doesnt contain the '>' symbol in the right position
	//then garbage coordinates are returned that the board will then display an error message for
	if(move.size() != 5 || move[2] != '>') {
		return std::make_pair(std::make_pair(-1, -1), std::make_pair(-1, -1));
	}

	//adjusts the input for the board's handling of coordinates
	int originCol = move[0] - 'a';
	int originrow = move[1] - '1';
	int destCol = move[3] - 'a';
	int destrow = move[4] - '1';

	return {{originrow, originCol}, {destrow, destCol} };
}
