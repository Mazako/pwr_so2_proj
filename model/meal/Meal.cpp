#include "Meal.h"
Meal::Meal(long id, std::string name, const std::deque<Step> &steps) : id(id), name(std::move(name)), steps(steps) {}

long Meal::getId() const {
    return id;
}

const std::string &Meal::getName() const {
    return name;
}

const std::deque<Step> &Meal::getSteps() const {
    return steps;
}