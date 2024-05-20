#include "Waiter.h"
#include <iostream>
#include <chrono>
#include <syncstream>

int Waiter::ID = 1;
static constexpr int DELIVERY_TIME_SECONDS = 5;

Waiter::Waiter(const std::shared_ptr<Kitchen> &kitchen, int x, int y, std::string letter) : MakeMove(x, y, letter){
    id = ID++;
    thread = std::thread(&Waiter::threadFunction, this, std::ref(kitchen));
}


void Waiter::threadFunction(const std::shared_ptr<Kitchen> &kitchen) {
    using std::cout;
    using std::endl;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        setX(100);
        this->order = kitchen->getReadyOrder();
        // cout << "(D) KELNER: " << id << " CZEKA" <<endl;
        if (order != nullptr) {
            setX(82);
            // cout << "(D) KELNER: " << id << " DOSTARCZA ZAMOWIENIE: " << order->getId() <<endl;
            std::this_thread::sleep_for(std::chrono::seconds(DELIVERY_TIME_SECONDS));
            // cout << "(D) KELNER: " << id << " UKONCZYL DOSTAWE ZAMOWIENIA: " << order->getId() <<endl;
            setX(120);
            this->order = nullptr;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}

void Waiter::start() {
    thread.join();
}

const std::string Waiter::getOrderInfo() {
    std::string info;

    if (order == nullptr) {
        info = "W" + std::to_string(id) + ": Waiting";
    } else {
        info = "W" + std::to_string(id) + ": Delivering " + order->getMeal().getName() + " (" +std::to_string(order->getId()) + ") ";
    }

    return info;
}