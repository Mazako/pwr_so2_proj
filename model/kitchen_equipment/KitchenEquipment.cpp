#include "KitchenEquipment.h"
#include <thread>
#include <chrono>


KitchenEquipment::KitchenEquipment(EquipmentType type, int y) : type(type), y(y) {}

bool KitchenEquipment::use(long time,
                           std::function<void(int)> xSetter,
                           std::function<void(int)> ySetter,
                           std::function<void(void)> basicYReset) {
    std::unique_lock<std::mutex> lock(mutex);
    while (busy) {
        basicYReset();
        xSetter(30);
        cv.wait(lock);
    }

    busy = true;
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

int KitchenEquipment::getY() const {
    return y;
}

EquipmentType KitchenEquipment::getType() const {
    return type;
}

void KitchenEquipment::setBroken(bool b) {
    this->broken = b;
}

void KitchenEquipment::notifyAll() {
    broken = false;
    cv.notify_one();
}
