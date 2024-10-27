#include "Board.cpp"


int main(){
    
    Board board;
    
    // start with white(white - odd, black - even)
    int turn = 1; 
    
    board.display();
    board.move(6, 0, 5, 0, turn);
    
    std::cout << std::endl;
    
    board.display();
    
    return 0;
}
