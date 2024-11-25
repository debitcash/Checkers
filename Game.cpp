#include <fstream>
#include "Game.h"
#include "User.h"

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

// updates the stats in a dedicated file
void Game::updateStats(User winner, User loser)
{
    std::string name;
    int wins, losses;
    bool foundWinner, foundLoser;
    
    // create array to store updated records
    std::vector<std::string> updatedRecords;
    
    // get records from the file in the stream
    std::ifstream records("stats.txt");  
    
    // keep reading the values line by line from the stream
    while (records >> name >> wins >> losses)
    {
        // if current user is in the records - update the User fields
        if (name == winner.getName())
        {
            wins = wins + 1;
            winner.setWins(wins);
            winner.setLosses(losses);
            foundWinner = true;
        }
        
        if (name == loser.getName())
        {
            losses = losses + 1;
            loser.setLosses(losses);
            loser.setWins(wins);
            foundLoser = true;
        }
        
        // provide new values to the vector
        updatedRecords.push_back(name + " " + std::to_string(wins) + " " + std::to_string(losses));
    }
    
    // if winner or looser are not in records, then create a new record for them
    if (!foundWinner)
    {
        updatedRecords.push_back(winner.getName() + " " + "1" + " " + "0");
    }
    
    if (!foundLoser)
    {
        updatedRecords.push_back(loser.getName() + " " + "0" + " " + "1");
    }
    
    // close records for reading
    records.close();
    
    std::cout << std::setw(2) << "\nThe winrate for " << winner.getName() << " is " << static_cast<int>(static_cast<float>(winner.getWins()) / (winner.getLosses() + winner.getWins()) * 100) << "%" << std::endl;
    
    std::cout << "The winrate for " << loser.getName() << " is " << static_cast<int>(static_cast<float>(loser.getWins()) / (loser.getLosses() + loser.getWins()) * 100) << "%" << std::endl;
    
    // populate the stats file with updated information
    std::ofstream newRecords("stats.txt");
    
    for (const std::string& record : updatedRecords) {
        newRecords << record << "\n";
    }

    newRecords.close(); 
}

//destructor for game
Game::~Game() {
    std::cout << "Game is over." << std::endl;
}
