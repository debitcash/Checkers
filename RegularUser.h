#ifndef REGULARUSER_H
#define REGULARUSER_H

#include <string>
#include "Board.h"
#include "User.h"

// RegularUser class represents a person using a terminal in PvP mode
class RegularUser : public User{
public:
    RegularUser();
    
    std::string getMove(Board originalBoard) override;
};

#endif //REGULARUSER_H
