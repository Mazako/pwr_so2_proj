#include "Cook.h"
#include <thread>
#include <chrono>
#include <iostream>

int Cook::ID = 1;

Cook::Cook(const std::shared_ptr<Kitchen> &kitchen, int x1, int y1, std::string letter) : MakeMove(x1, y1, letter) {
    id = ID++;
    thread = std::thread(&Cook::threadFunction, this, std::ref(kitchen));
    currentEq = EquipmentType::NOOP;
}


void Cook::threadFunction(const std::shared_ptr<Kitchen> &kitchen) {
    using std::cout;
    using std::endl;
    int basicPosition = getY();
    while (true) {
        // cout << "(G) KUCHARZ: " << id << ", CZEKAM NA ZAMOWIENIE" << endl;
        order = kitchen->getWaitingOrder();
        // cout << "(G) KUCHARZ: " << id << ", MAM ZAMOWIENIE: " << order->getId() << endl;
        for (const auto &step: order->getMeal().getSteps()) {
            auto eq = kitchen->getKitchenEquipment(step.getType());
            eq->use(step.getDurationInSeconds(),
                            [this](int x) { this->setX(x); },
                            [this](int y) { this->setY(y); },
                            [this, &basicPosition]() { this->setY(basicPosition); },
                            [this](EquipmentType type) { setCurrentEq(type); });
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
        info = "C" + std::to_string(id) +
               ": Cooking " + order->getMeal().getName() +
               " (" + std::to_string(order->getId()) + ") " +
               "   " + equipmentTypeToString(currentEq);
    }

    return info;
}

void Cook::setCurrentEq(EquipmentType currentEq) {
    Cook::currentEq = currentEq;
}
