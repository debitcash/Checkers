#include "Piece.cpp"

class Pawn : public Piece{
    private:

        bool isBlack;
        int originRow;
        int originCol;

    public:
        Pawn(bool newIsBlack, int newRow, int newCol) {
            isBlack = newIsBlack;
            originRow = newRow;
            originCol = newCol;
        }
        
        bool isBlackCheck()
        {
            return isBlack;
        }
        
        //check if move is valid(move forward only, can move in diagonal if capturing opposing color pieces)
        bool isValidMove(int destRow, int destCol) {
            //single space move
            if(originRow + 1 == destRow && originCol == destCol) {
                return true;
            }

            //double space move (only valid from starting position)
            if(originRow == 2){ //if the pawn is in the starting row
                if(originRow + 2 == destRow && originCol == destCol) {
                    return true;
                }
            }

            //diagonal capture move
            if((originRow + 1 == destRow) && ((originCol + 1 == destCol)|| (originCol - 1 == destCol))) {
                return true;
            }

            return false;

        }//end validMove

        void move(int destRow, int destCol, Piece* piece, Pawn* board[8][8]) {
            // assign the piece to new location and empty the previous location
            board[destRow][destCol] = board[originRow][originCol];
            // delete the object here?
            board[originRow][originCol] = nullptr;

            originRow = destRow;
            originCol = destCol;
        }
};
