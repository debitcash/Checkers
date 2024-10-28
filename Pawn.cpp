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
};
