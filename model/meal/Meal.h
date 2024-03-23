#ifndef SO2_ORDER_H
#define SO2_ORDER_H

#include "step.h"
#include <string>
#include <queue>

class Meal {
    long id;
    std::string name;
    std::queue<Step> steps;
};


#endif
