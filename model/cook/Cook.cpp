#include "Cook.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <syncstream>

int Cook::ID = 1;

Cook::Cook(const std::shared_ptr<Kitchen> &kitchen) {
    id = ID++;
    thread = std::thread(&Cook::threadFunction, this, std::ref(kitchen));
}

void Cook::threadFunction(const std::shared_ptr<Kitchen> &kitchen) {
    using std::cout;
    using std::endl;
    while (true) {
        cout << "ID: " << id << ", CZEKAM NA ZAMOWIENIE" << endl;
        order = kitchen->getWaitingOrder();
        cout << "ID: " << id << ", MAM ZAMOWIENIE: " << order->getId() << endl;
        for (const auto &step: order->getMeal().getSteps()) {
            auto eq = kitchen->getKitchenEquipment(step.getType());
            eq->use(step.getDurationInSeconds(), id);
            cout << "ID: " << id << ", SKONCZYLEM UZYWAC SPRZETU O ID " << eq->getId() << endl;
        }
        cout << "ID: " << id << ", SKONCZYLEM ZAMOWIENIE " << order->getId() << endl;
        kitchen->addReadyOrder(order);
        order = nullptr;
    }

}

void Cook::start() {
    thread.join();
}
