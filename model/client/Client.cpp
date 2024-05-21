#include "Client.h"


Client::Client(const std::shared_ptr<Kitchen> &kitchen, const Menu &menu) {
    this->thread = std::thread(&Client::threadFunction, this, std::ref(kitchen), std::ref(menu));
}

void Client::threadFunction(const std::shared_ptr<Kitchen> &kitchen, const Menu &menu) {
    while (true) {
        auto order = menu.createRandomOrder();
        kitchen->addWaitingOrder(order);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Client::start() {
    thread.join();
}
