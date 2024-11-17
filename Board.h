#include <iostream>
#include "Checker.h"
#include "Piece.h"


#ifndef BOARD_H
#define BOARD_H

class Board {

private:
    // declare the board and initialize the board values
    //(CHANGE: Jaisung) I have added that the board is now of a piece class, so it should take all of them.
    Piece* board[8][8] = {
        {nullptr, new Checker(false, false, 0, 1), nullptr, new Checker(false, false, 0, 3),
            nullptr, new Checker(false, false, 0, 5), nullptr, new Checker(false, false, 0, 7)}, // RED pieces
        {new Checker(false, false, 1, 0), nullptr, new Checker(false, false, 1, 2), nullptr,
            new Checker(false, false, 1, 4), nullptr, new Checker(false, false, 1, 6), nullptr},
        {nullptr, new Checker(false, false, 2, 1), nullptr, new Checker(false, false, 2, 3),
            nullptr, new Checker(false, false, 2, 5), nullptr, new Checker(false, false, 2, 7)},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {new Checker(true, false, 7 - 5, 7 - 0), nullptr, new Checker(true, false, 7 - 5, 7 - 2), nullptr,
            new Checker(true, false, 7 - 5, 7 - 4), nullptr, new Checker(true, false, 7 - 5, 7 - 6), nullptr},
        {nullptr, new Checker(true, false, 7 - 6, 7 - 1), nullptr, new Checker(true, false, 7 - 6, 7 - 3), nullptr,
            new Checker(true, false, 7 - 6, 7 - 5), nullptr, new Checker(true, false, 7 - 6, 7 - 7)},
        {new Checker(true, false, 7 - 7, 7 - 0), nullptr, new Checker(true, false, 7 - 7, 7 - 2), nullptr,
            new Checker(true, false, 7 - 7, 7 - 4), nullptr, new Checker(true, false, 7 - 7, 7 - 6), nullptr}}; // black pieces


public:
    void move(/*int originRow, int originCol, int destRow, int destCol,*/std::string input ,int& turn);

    void invertBoard();

    void display();

    bool checkForError(int originRow, int originCol, int destRow, int destCol, const int& turn, const Piece* chosenPiece);

};


#endif //BOARD_H
