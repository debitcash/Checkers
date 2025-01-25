#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Checker.h"
#include "KingChecker.h"
//#include "Game.h"

// Board class responsible for all the piece movements on the board, and visually displaying the game
class Board {
friend class Game;

private:
    // declare the board and initialize the board values
    // the board is now of a piece class, so it can contain both regular checkers and kings
    Piece* board[8][8] = {
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},// red pieces
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr},
        {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr}}; // black pieces
        
public:
    // no parameter constructor
    Board();
    
    // intialises the board with regular checker layout
    void initialise();
    
    // deep copy constructor
    Board(Board &originalBoard);
    
    // attempt to make a move provided by a user
    void attemptMove(std::string input, int& turn);
    
    // get all the available moves based on current board state for a certain piece color
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > getAvailableMovesForColor(bool isBlack);
    
    // service methods that provides hop moves to getAvailableMovesForColor method
    void findHopPaths(int row, int col, bool isBlack, std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > sequence,
            std::vector<  std::vector<std::pair<  std::pair<int, int>, std::pair<int, int> > > > &allSequences, bool isKingChecker);
                                    
    // move the piece and updates the board 
    void movePiece(std::pair<std::pair<int, int>, std::pair<int, int> >  move);
    
    // clear the heap memory, occupied by the board
    void cleanupBoardMemory();
    
    // inverts board to unify movement logic for both red and black checkers
    void invertBoard();
    
    // outputs the board to terminal
    void display() const;
    
    // promote a checker to king checker
    void checkPromotion(int originRow, int originCol);
    
    // get the difference between black and red pieces
    int getBlackMinusRed();
    
    // get the board array, used for tests only
    Piece* (*getBoard())[8];
};

#endif //BOARD_H
