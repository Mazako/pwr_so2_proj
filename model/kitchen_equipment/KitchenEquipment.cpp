#include "KitchenEquipment.h"
#include <thread>
#include <chrono>
#include <iostream>

long KitchenEquipment::ID = 1;

KitchenEquipment::KitchenEquipment(EquipmentType type, int y ) : type(type), id(ID++), y(y) {}

void KitchenEquipment::use(long time, long ids) {
    std::unique_lock<std::mutex> lock(mutex);
    while (busy) {
        cv.wait(lock);
    }

    busy = true;
    // std::cout << "(S) KUCHARZ: " << ids << ", UZYWAM TERAZ SPRZETU O ID " << id << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds (time));

    busy = false;
    cv.notify_one();
}

bool KitchenEquipment::isBusy() {
    std::lock_guard<std::mutex> lockGuard(mutex);
    return busy;
}

long KitchenEquipment::getId() const {
    return id;
}

int KitchenEquipment::getY() const {
    return y;
}

EquipmentType KitchenEquipment::getType() const {
    return type;
}
