#ifndef USER_H
#define USER_H

#include "Board.h"
#include <string>


class User {

private:
    std::string name;
    int wins, losses;

public:
    User(std::string Name);

    int getWins();

    int getLosses();
    
    void setWins(int);
    
    void setLosses(int);

    std::string getName();
};

#endif //USER_H
