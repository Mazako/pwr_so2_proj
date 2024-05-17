#include "MakeMove.h"

MakeMove::MakeMove(int x1, int y1, int x2, int y2, const char* letter){
    this->x1=x1;
    this->y1=y1;
    this->x2=x2;
    this->y2=y2;
    this->letter=letter;
}

void MakeMove::setX1(int x) {
    x1=x;
}

void MakeMove::setY1(int y) {
   y1=y;
}

void MakeMove::setX2(int x) {
   x2=x;
}

void MakeMove::setY2(int y) {
   y2=y;
}

int MakeMove::getX1() { return x1; }

int MakeMove::getY1() { return y1; }

int MakeMove::getX2() { return x2; }

int MakeMove::getY2() { return y2; }

const char* MakeMove::getLetter() {
    return letter;
}
