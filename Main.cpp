#include "Board.cpp"



int main(){
    
    Board board;
    
    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();
    //board.newMove(1, 0, 2, 0, turn);
    //board.newMove(7,0,6,0,turn);
    
    board.newMove(1,0,3,0,turn);
    
    std::cout << "Just testing" << std::endl; //Just testing if the programming is running past this point.
    
    std::cout << std::endl;
    //just to increment the turn++
    std::cout << "Just test" << std::endl;
    //turn++;
    
    board.display();
    
    std::cout << std::endl;
    
   // board.newMove(7,0,6,0,turn);
    
    board.display();

    //std::cout << std::endl;
    std::cout << "Just testing" << std::endl; 
    
    board.display();
    
    std::cout << std::endl;
    

    return 0;
}
