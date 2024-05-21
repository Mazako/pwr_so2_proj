#include "Meal.h"
Meal::Meal(std::string name, const std::deque<Step> &steps) : name(std::move(name)), steps(steps) {}

const std::string &Meal::getName() const {
    return name;
}

const std::deque<Step> &Meal::getSteps() const {
    return steps;
}