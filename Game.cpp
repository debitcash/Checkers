
#include "Game.h"

Game::Game() {
    //odd turns are red, black are even
    turn = 1;
}

void Game::play() {
    std::string input;

    board.display();

    std::cout << currentColor() << "'s turn." << std::endl;
    std::getline(std::cin, input);

    board.attemptMove(input, turn);

}

bool Game::endGame() {
    bool hasMove = false;

    //check if any pieces of the current turn color are moveable
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = board.board[row][col];

            //if there is a piece at that location, and the piece is the right color for the turn
            if (piece != nullptr && piece->isBlackCheck() == (turn % 2 == 0)) {
                //just checking whether there is at least one piece of the right color on the board
                return false;

                //need to somehow determine if that piece has a valid move.
                //not sure how to do this cleanly since board checks validity of moves
                //based on coordinates and piece checks validity of moves not in relation to other pieces

                //right now I have it checking just if all the pieces are captured or not,
                //but techincally it should also check if the only remaining pieces are stuck/trapped

            }
        }
    }

    return true;
}

//getter for turn variable
int Game::getTurn() const{
    return turn;
}

//returns the current colour based on what turn it is
std::string Game::currentColor() const {
    return turn % 2 == 0 ? "Black" : "Red";
}

//destructor for game
Game::~Game() {
    std::cout << "Game is over." << std::endl;
}