#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "User.h"


// header for Game class that is responsible for game management
class Game {

private:
    // stores current turn
    int turn;
    Board board;

public:
    Game();

    // starts new game
    void play();

    // ends game
    bool endGame();
    
    int getTurn() const;
    
    std::string currentColor() const;
    
    // updates stats.txt with latest information
    void updateStats(User& winner, User& loser);

    ~Game();
};

#endif //GAME_H
