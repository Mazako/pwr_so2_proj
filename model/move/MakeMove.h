 class MakeMove{
    
    int x1,y1,x2,y2;
    const char* letter;


    public:
        MakeMove(int x1,int y1,int x2,int y2, const char* letter);
        void setX1(int x);
        void setY1(int y);
        void setX2(int x);
        void setY2(int y);
        int getX1();
        int getY1();
        int getX2();
        int getY2();
        const char* getLetter();

};