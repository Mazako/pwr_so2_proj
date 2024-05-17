#include "Order.h"
#include <iostream>
#include <utility>

long Order::ID = 1;

Order::~Order() {
    // std::cout << "KONIEC" << std::endl;
}

Order::Order(long clientId, Meal meal1) : id(ID++),  clientId(clientId), meal(std::move(meal1)), status(OrderStatus::WAITING) {

}

const Meal &Order::getMeal() const {
    return meal;
}

long Order::getClientId() const {
    return clientId;
}

const std::atomic<OrderStatus> &Order::getStatus() const {
    return status;
}

long Order::getId() const {
    return id;
}
