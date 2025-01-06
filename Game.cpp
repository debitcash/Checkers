#include <fstream>
#include "Game.h"
#include "User.h"
#include "AiUser.cpp"

// file that holds all the logic relateble to Game class

// game constructor
Game::Game() 
{
    //odd turns are red, black are even
    turn = 1;
    board.initialise();
}

void Game::play(User* ptrUser1, User* ptrUser2)
{
    std::string providedMove;
    board.display();
    
    // display who should move now and get the coordinates as input
    std::cout << currentColor() << "'s turn." << std::endl;
    
    if (currentColor() == "Red")
        providedMove = ptrUser1->getMove(board);
    else
    {
        board.display();
        providedMove = ptrUser2->getMove(board);
    }
    
    if (providedMove == "Give up")
    {
        giveUp = true;
        return;
    }
    
    // check if provided move is valid
    board.attemptMove(providedMove, turn);
    
}

// check if players have any remaining pieces on the board
bool Game::endGame() 
{
    if (giveUp)
        return true;
    
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            Piece* piece = board.board[row][col];

            // if there is a piece at that location, and the piece is the right color for the turn
            if (piece != nullptr && piece->isBlackCheck() == (turn % 2 == 0)) {
                return false;
            }
        }
    }
    
    return true;
}

// getter for turn variable
int Game::getTurn() const{
    return turn;
}

// returns the current colour based on what turn it is
std::string Game::currentColor() const {
    return turn % 2 == 0 ? "Black" : "Red";
}

// update the stats in a dedicated file
void Game::updateStats(User& winner, User& loser)
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
    
    // if winner or loser is not in records, create a new record for them
    if (!foundWinner)
    {
        updatedRecords.push_back(winner.getName() + " " + "1" + " " + "0");
        winner.setWins(1);
        winner.setLosses(0);
    }
    
    if (!foundLoser)
    {
        updatedRecords.push_back(loser.getName() + " " + "0" + " " + "1");
        loser.setWins(0);
        loser.setLosses(1);
    }
    
    // close records for reading
    records.close();
    
    std::cout << "\nThe winrate for " << winner.getName() << " is " << static_cast<int>(static_cast<float>(winner.getWins()) / (winner.getLosses() + winner.getWins()) * 100) << "%" << std::endl;
    
    std::cout << "The winrate for " << loser.getName() << " is " << static_cast<int>(static_cast<float>(loser.getWins()) / (loser.getLosses() + loser.getWins()) * 100) << "%" << std::endl;
    
    // populate the stats file with updated information
    std::ofstream newRecords("stats.txt");
    
    for (const std::string& record : updatedRecords) {
        newRecords << record << "\n";
    }

    newRecords.close(); 
}

// destructor for game
Game::~Game() {
    std::cout << "Game is over." << std::endl;
    board.cleanupBoardMemory( );
}
