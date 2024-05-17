#ifndef SO2_ORDER_H
#define SO2_ORDER_H

#include <string>
#include <queue>
#include <utility>
#include "Step.h"

class Meal {
public:
    Meal(long id, std::string name, const std::deque<Step> &steps);

private:
    long id;
    std::string name;
    std::deque<Step> steps;

public:
    long getId() const;

    const std::string &getName() const;

    const std::deque<Step> &getSteps() const;
};
#endif
