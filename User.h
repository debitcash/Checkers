#ifndef USER_H
#define USER_H

//#include "Board.h"
#include <string>

// user class headers

class User {

// data members
private:
    std::string name;
    int wins, losses;

public:
    User(std::string Name);
    
    User();
    
    // setters and getters for data members
    int getWins();

    int getLosses();
    
    void setWins(int);
    
    void setLosses(int);

    std::string getName();
    void setName(std::string newName);
};

#endif //USER_H
