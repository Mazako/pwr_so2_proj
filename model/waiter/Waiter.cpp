#include "Waiter.h"
#include <iostream>
#include <chrono>
#include <syncstream>

int Waiter::ID = 1;
static constexpr int DELIVERY_TIME_SECONDS = 5;

Waiter::Waiter(const std::shared_ptr<Kitchen> &kitchen){
    id = ID++;
    thread = std::thread(&Waiter::threadFunction, this, std::ref(kitchen));
}


void Waiter::threadFunction(const std::shared_ptr<Kitchen> &kitchen) {
    using std::cout;
    using std::endl;
    while (true) {
        std::shared_ptr<Order> order = kitchen->getReadyOrder();
        cout << "(D) KELNER: " << id << " CZEKA" <<endl;
        if (order != nullptr) {
            cout << "(D) KELNER: " << id << " DOSTARCZA ZAMOWIENIE: " << order->getId() <<endl;
            std::this_thread::sleep_for(std::chrono::seconds(DELIVERY_TIME_SECONDS));
            cout << "(D) KELNER: " << id << " UKONCZYL DOSTAWE ZAMOWIENIA: " << order->getId() <<endl;
        }
    }
}

void Waiter::start() {
    thread.join();
}

