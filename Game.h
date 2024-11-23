
#ifndef GAME_H
#define GAME_H

#include "Board.h"



class Game {

private:
    int turn;
    Board board;

public:
    Game();

    void play();

    bool endGame();

    int getTurn() const;

    std::string currentColor() const;

    ~Game();
};

#endif //GAME_H
