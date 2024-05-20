 class MakeMove{
    
    int x,y;
    const char* letter;


    public:
        MakeMove(int x, int y, const char *letter);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        const char* getLetter();

};