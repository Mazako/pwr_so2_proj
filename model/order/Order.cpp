#include "Order.h"
#include <utility>

long Order::ID = 1;

Order::Order(Meal meal1) : id(ID++), meal(std::move(meal1)) {

}

const Meal &Order::getMeal() const {
    return meal;
}

long Order::getId() const {
    return id;
}
