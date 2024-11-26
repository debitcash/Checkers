#include "User.h"

// user class makes it easier to store and process stats
User::User(std::string newName)
{
    name = newName;
}

// constructor
std::string User::getName()
{
    return name;
}

// setters and getter for all the datamembers
int User::getWins()
{
    return wins;
}

int User::getLosses()
{
    return losses;
}

void User::setWins(int newWins)
{
    wins = newWins;
}

void User::setLosses(int newLosses)
{
    losses = newLosses;
}
