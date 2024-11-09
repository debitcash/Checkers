#include "Board.cpp"



int main(){
    
    Board board;
    
    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();
    //board.newMove(1, 0, 2, 0, turn)
	
	
	
    board.newMove(6,1,5,1,turn);
    board.display();
    
    
    
    
    /*board.newMove(1,0,2,0,turn);
    board.display();
    std::cout << "Ended first move\n";
    
    
    board.newMove(2,0,3,0,turn);
    board.display();
    std::cout << "Ended second move\n";
    
    board.newMove(3,0,4,0,turn);
    board.display();
    std::cout << "Ended third move\n";
    
    board.newMove(4,0,5,0,turn);
    board.display();
    std::cout << "Ended forth move\n";
    
    board.newMove(5,0,6,1,turn);
    board.display();
    std::cout << "Ended six move\n";
    
    board.newMove(6,1,7,2,turn);
    board.display();
    std::cout << "Ended sevens move\n";*/

    

    /*
    board.newMove(4,0,5,0,turn);
    board.display();
    std::cout << "Ended fifth move\n";*/
    
    
    
    std::cout << "Just testing" << std::endl; //Just testing if the programming is running past this point.
    
    //turn++;
    
    
    

    

    return 0;
}
