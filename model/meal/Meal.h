#ifndef SO2_ORDER_H
#define SO2_ORDER_H

#include <string>
#include <queue>
#include <utility>
#include "Step.h"

class Meal {
public:
    Meal(std::string name, const std::deque<Step> &steps);

private:
    std::string name;
    std::deque<Step> steps;

public:

    const std::string &getName() const;

    const std::deque<Step> &getSteps() const;
};
#endif
