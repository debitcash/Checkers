#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "User.h"


// Game class responsible for game management
class Game {
private:
    // stores current turn
    int turn;
    Board board;
    bool giveUp = false;

public:
    Game();

    // starts new game
    void play(User* ptrUser1, User* ptrUser2);
    
    void pvpPlay();
    
    void aiPlay();

    // ends game
    bool endGame();
    
    int getTurn() const;
    
    std::string currentColor() const;
    
    // updates stats.txt with latest information
    void updateStats(User& winner, User& loser);

    ~Game();
};

#endif //GAME_H
