#include "Board.cpp"



int main(){
    
    Board board;
    
    // start with white(white - odd, black - even)
    // white at bottom black at top
    int turn = 1; 
    
    board.display();
    //board.newMove(1, 0, 2, 0, turn)
	
	bool stalemate = false, checkmate = false;
    
    while (!checkmate || !stalemate)
    {
        int originRow, originCol, destRow, destCol;
        
        std::cout << std::endl << "Provide the move in a form originRow originCol destRow destCol." << std::endl;
        std::cin >> originRow >> originCol >> destRow >> destCol ;
        
        board.move(originRow, originCol, destRow, destCol, turn);
        
    }
    

    return 0;
}
