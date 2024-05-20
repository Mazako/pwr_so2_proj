#include "KitchenEquipment.h"
#include <thread>
#include <chrono>
#include <iostream>

long KitchenEquipment::ID = 1;

KitchenEquipment::KitchenEquipment(EquipmentType type, int y) : type(type), id(ID++), y(y) {}

bool KitchenEquipment::use(long time,
                           std::function<void(int)> xSetter,
                           std::function<void(int)> ySetter,
                           std::function<void(void)> basicYReset,
                           std::function<void(EquipmentType)> kitchenEqSetter) {
    std::unique_lock<std::mutex> lock(mutex);
    while (busy) {
        basicYReset();
        xSetter(30);
        cv.wait(lock);
    }

    busy = true;
    kitchenEqSetter(type);
    // std::cout << "(S) KUCHARZ: " << ids << ", UZYWAM TERAZ SPRZETU O ID " << id << std::endl;
    long millis = time * 1000;
    long current = 0;
    while (current <= millis) {
        xSetter(12);
        ySetter(y);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        while (broken) {
            xSetter(30);
            basicYReset();
            cv.wait(lock);
        }
        current += 100;
    }
    xSetter(30);
    basicYReset();
    busy = false;
    cv.notify_all();
    return true;
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

bool KitchenEquipment::isBroken() const {
    return broken;
}

void KitchenEquipment::setBroken(bool b) {
    this->broken = b;
}

void KitchenEquipment::notifyAll() {
    broken = false;
    cv.notify_one();
}
