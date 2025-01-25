// allows for colour usability
//#include <windows.h>
#include <iomanip>
#include <sstream>
#include <typeinfo>


#include "Game.h"

#include "User.h"
#include "RegularUser.h"
#include "NetworkUser.h"
#include "AiUser.h"
#include "Server.h"
#include "Client.h"

#include "Board.h"
#include "Checker.h"
#include "Piece.h"
#include "KingChecker.h"



// file that contaings control flow for main  logic
int main(){

	//allows for colour printout in the terminal
	//system(("chcp " + std::to_string(CP_UTF8)).c_str());

    // welcome the use and display game instructions
	std::cout << "\t\tWelcome to checkers!" << std::endl;
	std::cout << "|********************************************************************|" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "Checkers is a two-player game, where each player moves pieces" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "diagonally. Pieces can move one square forward or capture an" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "opponent's piece by jumping over it to an empty square. Kings" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "(created when a piece reaches the opponent's back row) can move" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "both forward and backward. The goal is to capture all opponent" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "pieces or block them so they can't move." <<" |" << std::endl;
	std::cout << "|--------------------------------------------------------------------|" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "Provide moves in the form row+col>row+col" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(61) << std::left <<  "\teg. b3>c4" << " |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "To perform multiple jump moves, enter the first set of" <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(65) << std::left <<  "coordinates, a space " ", then the second set of coordinates. " <<" |" << std::endl;
	std::cout << "|  " <<  std::setw(61) << std::left <<  "\teg. b3>d5 "
													   ""
				"d5>b7" <<" |" << std::endl;
	std::cout << "|********************************************************************|" << std::endl;
	std::cout << "\t\tHave fun!" << std::endl << std::endl;

    // set up a game
	Game game;
    
    User* ptrUser1;
    User* ptrUser2;    
    
    std::string gameStyle;
    
    std::cout << "What kind of game would you like to play?" << std::endl;
    
    // choose the style of the game
    while (gameStyle != "PvP" && gameStyle != "PvAI" && gameStyle != "Network")
    {
        std::cout << "Available options: \"PvP\" \"PvAI\" \"Network\"." << std::endl;
        std::getline(std::cin, gameStyle);
    }
    
    // launch a game with appropriate users
    if (gameStyle == "PvP")
    {
        ptrUser1 = new RegularUser();
        ptrUser2 = new RegularUser();
        
        while (!game.endGame())
        {
            game.play(ptrUser1, ptrUser2);
        }
    }
    
    else if (gameStyle == "PvAI")
    {
        ptrUser1 = new RegularUser();
        ptrUser2 = new AiUser();
        
        while (!game.endGame())
        {
            game.play(ptrUser1, ptrUser2);
        }
    }
    
    else if (gameStyle == "Network")
    {
        std::string decision = "";
        std::cout << "\nIs this user a client or a server?" << std::endl;
        
        while (decision != "Client" && decision != "Server")
        {
            std::cout << "Available options: \"Client\" or \"Server\". " <<std::endl;
            std::getline(std::cin, decision );
        }
        
        if (decision == "Server")
        {
            ptrUser1 = new Server(true);
            ptrUser2 = new Client(true);
        }
        
        else
        {
            ptrUser1 = new Server(false);
            ptrUser2 = new Client(false);
        }
        
        while (!game.endGame())
        {
            game.play(ptrUser1, ptrUser2);
        }
    }
    
    // provide information and statistics at the end of the game
    std::cout << game.currentColor() << " lost! " << std::endl;
	std::cout << "The game lasted " << game.getTurn() << " moves." << std::endl;
	std::cout << std::endl << "Thanks for playing" << std::endl;
    
    // recording the info from this game into a file
    // the first user parameter in the function call is a winner
    if (game.currentColor() == "Black")
        game.updateStats(*ptrUser1, *ptrUser2);
    else
        game.updateStats(*ptrUser2, *ptrUser1);
        
    // cleanup the memory
    delete ptrUser1;
    delete ptrUser2;
    
    return 0;
}
