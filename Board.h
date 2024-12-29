#include <iostream>
#include "Checker.h"
#include "KingChecker.h"
#include "Game.h"
#include <vector>

// a header for class that is responsible for all the piece movements on the board, and visually displaying the game

#ifndef BOARD_H
#define BOARD_H

class Board {

    friend class Game;

private:
    // declare the board and initialize the board values
    // the board is now of a piece class, so it can contain both regular checkers and kings
    Piece* board[8][8] = {
        {nullptr, new Checker(false, false, 0, 1,false), nullptr, new Checker(false, false, 0, 3,false),
            nullptr, new Checker(false, false, 0, 5,false), nullptr, new Checker(false, false, 0, 7,false)}, // red pieces
        {new Checker(false, false, 1, 0,false), nullptr, new Checker(false, false, 1, 2,false), nullptr,
            new Checker(false, false, 1, 4,false), nullptr, new Checker(false, false, 1, 6,false), nullptr},
        {nullptr, new Checker(false, false, 2, 1,false), nullptr, new Checker(false, false, 2, 3,false),
            nullptr, new Checker(false, false, 2, 5,false), nullptr, new Checker(false, false, 2, 7,false)},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {new Checker(true, false, 7 - 5, 7 - 0, false), nullptr, new Checker(true, false, 7 - 5, 7 - 2, false), nullptr,
            new Checker(true, false, 7 - 5, 7 - 4, false), nullptr, new Checker(true, false, 7 - 5, 7 - 6, false), nullptr},
        {nullptr, new Checker(true, false, 7 - 6, 7 - 1, false), nullptr, new Checker(true, false, 7 - 6, 7 - 3, false), nullptr,
            new Checker(true, false, 7 - 6, 7 - 5, false), nullptr, new Checker(true, false, 7 - 6, 7 - 7, false)},
        {new Checker(true, false, 7 - 7, 7 - 0, false), nullptr, new Checker(true, false, 7 - 7, 7 - 2, false), nullptr,
            new Checker(true, false, 7 - 7, 7 - 4, false), nullptr, new Checker(true, false, 7 - 7, 7 - 6, false), nullptr}}; // black pieces
        
public:
    
    // no parameter constructor
    Board();
    
    // deep copy constructor
    Board(Board &originalBoard);
    
    Piece* (*getBoard())[8][8];

    // attempt to make a move to provided coordinates
    void attemptMove(std::string input, int& turn);
    
    // inverts board to unify movement logic for both red and black checkers
    void invertBoard();
    
    // outputs the board to terminal
    void display() const;

    // checks for user input errors
    bool checkForError(int originRow, int originCol, int destRow, int destCol, const int& turn, const Piece* chosenPiece);
    
    // check if the capture move has valid coordinates
    bool captureMoveCheck(int originRow, int originCol, int destRow, int destCol, int& turn);
    
    // checks if the piece is kingChecker
    void checkPromotion(int originRow, int originCol);
    
    // get the pieces difference
    int getBlackMinusRed();
};

#endif //BOARD_H
