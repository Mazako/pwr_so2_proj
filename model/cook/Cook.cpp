#include "Cook.h"
#include <thread>
#include <chrono>
#include <iostream>
#include <syncstream>

int Cook::ID = 1;

Cook::Cook(const std::shared_ptr<Kitchen> &kitchen, int x1, int y1, const char* letter) : MakeMove(x1, y1, letter) {
    id = ID++;
    thread = std::thread(&Cook::threadFunction, this, std::ref(kitchen));
}


void Cook::threadFunction(const std::shared_ptr<Kitchen> &kitchen) {
    using std::cout;
    using std::endl;
    while (true) {
        // cout << "(G) KUCHARZ: " << id << ", CZEKAM NA ZAMOWIENIE" << endl;
        order = kitchen->getWaitingOrder();
        // cout << "(G) KUCHARZ: " << id << ", MAM ZAMOWIENIE: " << order->getId() << endl;
        for (const auto &step: order->getMeal().getSteps()) {
            auto eq = kitchen->getKitchenEquipment(step.getType());
            setX(12);
            setY(eq->getY());
            eq->use(step.getDurationInSeconds(), id);
            // cout << "(G) KUCHARZ: " << id << ", SKONCZYLEM UZYWAC SPRZETU O ID " << eq->getId() << endl;
        }
        setX(47);
        // cout << "(G) KUCHARZ: " << id << ", SKONCZYLEM ZAMOWIENIE " << order->getId() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        kitchen->addReadyOrder(order);
        setX(30);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        order = nullptr;
    }

}


void Cook::start() {
    thread.join();
}

const std::string Cook::getOrderInfo() {
    std::string info;

    if (order == nullptr) {
        info = "C" + std::to_string(id) + ": No order";
    } else {
        info = "C" + std::to_string(id) + ": " + order->getMeal().getName() + " (" +std::to_string(order->getId()) + ") ";
    }

    return info;
}
