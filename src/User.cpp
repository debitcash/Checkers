#include "User.h"
#include "Board.h"
#include <iostream>

// default constructor just in case
User::User()
{}

// virtualized method that gets a move path from a user
std::string User::getMove(Board originalBoard)
{
    return "Default string as user input. To be overridden!";
}

// setters and getter sfor all the datamembers
int User::getCount()
{
    userCount++;
    return userCount;
}

std::string User::getName()
{
    return name;
}

void User::setName(std::string newName)
{
    name = newName;
}


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
