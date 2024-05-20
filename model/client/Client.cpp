#include "Client.h"

long Client::ID = 1;

Client::Client(const std::shared_ptr<Kitchen> &kitchen, const Menu &menu) {
    this->id = ID++;
    this->thread = std::thread(&Client::threadFunction, this, std::ref(kitchen), std::ref(menu));
}

void Client::threadFunction(const std::shared_ptr<Kitchen> &kitchen, const Menu &menu) {
    while (true) {
        auto order = menu.createRandomOrder(1);
        kitchen->addWaitingOrder(order);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Client::start() {
    thread.join();
}
