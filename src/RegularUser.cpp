#include <iostream>
#include "Board.h"
#include "RegularUser.h"

RegularUser::RegularUser()
{
    std::string newName;
    
    std::cout << "Provide the name of player" << getCount() << ": " << std::endl;
    std::getline(std::cin, newName);
    
    setName(newName);
}

// overridden method that gets a move path from a user
std::string RegularUser::getMove(Board originalBoard)
{
    std::string typedMove;
    std::getline(std::cin, typedMove);
    
    return typedMove;
}
