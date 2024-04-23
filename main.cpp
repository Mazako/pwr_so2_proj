#include <iostream>
#include <vector>
#include <thread>
#include "KitchenEquipment.h"
#include "Waiter.h"
#include "Kitchen.h"
#include "Cook.h"


[[noreturn]] void clientSimulatorThreadFunction(Menu &menu, const std::shared_ptr<Kitchen> &kitchen) {
    while (true) {
        auto order = menu.createRandomOrder(1);
        kitchen->addWaitingOrder(order);
        std::this_thread::sleep_for(std::chrono::seconds(8));
    }
}

// (G) - GOTOWANIE
// (D) - DOSTAWA
// (S) - SPRZĘT

int main() {
    auto kitchen = std::make_shared<Kitchen>();
    auto menu = Menu();

    std::thread clientSimulator(clientSimulatorThreadFunction, std::ref(menu), std::ref(kitchen));

    auto cook1 = std::make_unique<Cook>(kitchen);
    auto cook2 = std::make_unique<Cook>(kitchen);
    auto waiter1 = std::make_unique<Waiter>(kitchen);
    auto waiter2 = std::make_unique<Waiter>(kitchen);

    cook1->start();
    cook2->start();
    waiter1->start();
    waiter2->start();
    clientSimulator.join();
}

