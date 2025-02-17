#ifndef USER_H
#define USER_H

#include <string>
#include "Board.h"

// User class provides general functionality for a specific user
class User {
private:
    std::string name;
    int wins, losses;
    static int userCount;

public:
    
    User();
    ~User();
    
    // gets a move path from a user
    virtual std::string getMove(Board originalBoard);
    
    // setters and getters for data members
    int getCount();
    
    int getWins();

    int getLosses();
    
    virtual std::string getName();
    
    void setWins(int);
    
    void setLosses(int);
    
    void setName(std::string newName);
    
    void enforceCaptureMove(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > &allMoves);
};

#endif //USER_H
