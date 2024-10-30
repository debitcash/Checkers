class Pawn{
    private:
        //
        bool isBlack;
    public:
        Pawn(bool newIsBlack): isBlack(newIsBlack){}
        
        bool isBlackCheck()
        {
            return isBlack;
        }
        
        //check if move is valid(move forward only, can move in diagonal if capturing opposing color pieces)
        bool isValidMove(int row1, int column1, int row2, int column2)
        {
            //black pawn can only move down(relative to the terminal window) or diagonally for capture
            if (isBlack && (row1 + 1 == row2 && column1 == column2))
            {
                return true;
            }
            
            //white can only move up(relative to terminal window) or diagonally for capture
            else if (!isBlack && (row1 == row2 + 1 && column1 == column2) )
            {
                return true;
            }
            
            return false;
        }
};
