#include "Board.cpp"



int main(){
    
    Board board;
    
    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();
    board.newMove(1, 0, 2, 0, turn);
    
    std::cout << std::endl;
    
    board.display();
    
    /*board.invertBoard();
    
    std::cout << std::endl;
    std::cout << std::endl;
    
    board.display();
    
    std::cout << std::endl;
    std::cout << std::endl;
    board.invertBoard();
    
    board.display();*/
    
    return 0;
}
