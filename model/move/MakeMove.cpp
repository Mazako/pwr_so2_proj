#include "MakeMove.h"

MakeMove::MakeMove(int x, int y, std::string letter) {
    this->x = x;
    this->y = y;
    this->letter = letter;
}

void MakeMove::setX(int x) {
    this->x = x;
}

void MakeMove::setY(int y) {
    this->y = y;
}

int MakeMove::getX() { return x; }

int MakeMove::getY() { return y; }

std::string MakeMove::getLetter() {
    return letter;
}

