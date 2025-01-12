#ifndef AIUSER_H
#define AIUSER_H

#include <iostream>
#include <vector>
#include "Board.h"
#include "User.h"

// AiUser class holds all the logic related to minimax calculations
class AiUser : public User {
private:
    // store best possible move
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > >  optimalMove;
    
    //store the depth for minimax discovery
    int maxDepth;
    
public:
    // default constructor
    AiUser();
    
    // get the move, following minimax algorithm
    std::string getMove(Board originalBoard) override;
    
    int miniMaxResult(Board boardOrig, bool isMaxPlayer, int depth, int pruningAlpha, int pruningBeta);
};

#endif //AIUSER_H
