#include "User.h"
#include "Board.h"
#include <iostream>

int User::userCount = 0;

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

User::~User()
{}

// service method, deletes the single row moves from all available moves, if capture moves are available
// this makes capture moves unavoidable
void User::enforceCaptureMove(std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > &allMoves)
{
    bool captureMovePresent = false;
    std::vector<std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > > newMoves;
    
    // if capturemove is found in population of moves, raise the flag that capture moves should be enforced
    for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > move : allMoves)
    {
        if (move.size() > 1 || move[0].first.first + 2 == move[0].second.first || move[0].first.first - 2 == move[0].second.first)
        {
            captureMovePresent = true;
            break;
        }
    }
    
    // if capture move flag is raised
    if (captureMovePresent)
    {
        // select only the capture moves as available moves, even though single rows are also possible
        for (std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > move : allMoves)
        {   
            if (move.size() > 1 || move[0].first.first + 2 == move[0].second.first || move[0].first.first - 2 == move[0].second.first)
            {
                newMoves.push_back(move);
            }
        }
        allMoves = newMoves;
    }
}
