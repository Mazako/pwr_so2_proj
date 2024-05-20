#include "Kitchen.h"

Kitchen::Kitchen() {
    equipment.emplace(EquipmentType::PAN, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::PAN, 1)
    });
    equipment.emplace(EquipmentType::COOKER, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::COOKER, 3)
    });
    equipment.emplace(EquipmentType::OVEN, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::OVEN, 5)
    });
    equipment.emplace(EquipmentType::TABLE, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::TABLE, 7)
    });
    equipment.emplace(EquipmentType::MIXER, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::MIXER, 9)
    });
    equipment.emplace(EquipmentType::MICROVAVE, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::MICROVAVE, 11)
    });

}

void Kitchen::addWaitingOrder(const std::shared_ptr<Order> &order) {
    std::lock_guard<std::mutex> lock(waitingOrdersMutex);
    waitingOrders.push_back(order);
    waitingOrdersCV.notify_all();
}

std::shared_ptr<Order> Kitchen::getWaitingOrder() {
    std::unique_lock<std::mutex> lock(waitingOrdersMutex);

    while (waitingOrders.empty()) {
        waitingOrdersCV.wait(lock);
    }

    auto order = waitingOrders.front();
    waitingOrders.pop_front();
    return order;
}

void Kitchen::addReadyOrder(const std::shared_ptr<Order> &order) {
    std::lock_guard<std::mutex> lock(readyOrdersMutex);
    readyOrders.push_back(order);
    readyOrdersCV.notify_one();
}

std::shared_ptr<Order> Kitchen::getReadyOrder() {
    std::unique_lock<std::mutex> lock(readyOrdersMutex);

    while (readyOrders.empty()) {
        readyOrdersCV.wait(lock);
    }

    auto order = readyOrders.front();
    readyOrders.pop_front();
    readyOrdersCV.notify_all();
    return order;
}

std::shared_ptr<KitchenEquipment> Kitchen::getKitchenEquipment(EquipmentType equipmentType) {
    auto vec = equipment.at(equipmentType);
    return vec[0];
}

const std::map<EquipmentType, std::vector<std::shared_ptr<KitchenEquipment>>> &Kitchen::getEquipment() const {
    return equipment;
}

const std::deque<std::shared_ptr<Order>> &Kitchen::getWaitingOrders() const {
    return waitingOrders;
}

const std::deque<std::shared_ptr<Order>> &Kitchen::getReadyOrders() const {
    return readyOrders;
}

void Kitchen::breakEverything() {
    for (const auto &item: equipment) {
        for (const auto &eq: item.second) {
            eq->setBroken(true);
        }
    }
    broken = true;
}

void Kitchen::fixEverything() {
    for (const auto &item: equipment) {
        for (const auto &eq: item.second) {
            eq->notifyAll();
        }
    }
    broken = false;
}

bool Kitchen::isBroken() const {
    return broken;
}


