#include "KitchenEquipment.h"
#include <thread>
#include <chrono>
#include <iostream>

long KitchenEquipment::ID = 1;

KitchenEquipment::KitchenEquipment(EquipmentType type) : type(type), id(ID++) {}

void KitchenEquipment::use(long time, long ids) {
    std::unique_lock<std::mutex> lock(mutex);
    while (busy) {
        cv.wait(lock);
    }

    busy = true;

    std::this_thread::sleep_for(std::chrono::seconds (time));

    busy = false;
    cv.notify_one();
}

bool KitchenEquipment::isBusy() {
    return busy;
}

long KitchenEquipment::getId() const {
    return id;
}
