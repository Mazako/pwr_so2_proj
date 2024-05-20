#ifndef SO2_PROJ_MAKEMOVE_H
#define SO2_PROJ_MAKEMOVE_H

#include <string>

class MakeMove{
    
    int x,y;
    std::string letter;


    public:
        MakeMove(int x, int y, std::string letter);
        void setX(int x);
        void setY(int y);
        int getX();
        int getY();
        std::string getLetter();

};

#endif