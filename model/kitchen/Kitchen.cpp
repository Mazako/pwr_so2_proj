#include "Kitchen.h"

Kitchen::Kitchen() {
    equipment.emplace(EquipmentType::PAN, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::PAN)
    });
    equipment.emplace(EquipmentType::COOKER, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::COOKER)
    });
    equipment.emplace(EquipmentType::OVEN, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::OVEN)
    });
    equipment.emplace(EquipmentType::TABLE, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::TABLE)
    });
    equipment.emplace(EquipmentType::MIXER, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::MIXER)
    });
    equipment.emplace(EquipmentType::MICROVAVE, std::vector<std::shared_ptr<KitchenEquipment>> {
            std::make_shared<KitchenEquipment>(EquipmentType::MICROVAVE)
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

    auto order = waitingOrders.back();
    waitingOrders.pop_back();
    return order;
}

void Kitchen::addReadyOrder(const std::shared_ptr<Order> &order) {
    std::lock_guard<std::mutex> lock(readyOrdersMutex);
    readyOrders.push_back(order);
}

std::shared_ptr<Order> Kitchen::getReadyOrder() {
    std::unique_lock<std::mutex> lock(readyOrdersMutex);

    while (readyOrders.empty()) {
        readyOrdersCV.wait(lock);
    }

    auto order = readyOrders.back();
    readyOrders.pop_back();
    readyOrdersCV.notify_all();
    return order;
}

std::shared_ptr<KitchenEquipment> Kitchen::getKitchenEquipment(EquipmentType equipmentType) {
    std::unique_lock<std::mutex> lock(equipmentMutex);

    auto vec = equipment.at(equipmentType);
    std::shared_ptr<KitchenEquipment> found = nullptr;
    do {
        for (const auto &eq: vec) {
            if (!eq->isBusy()) {
                found = eq;
                break;
            }
        }
        if (found == nullptr) {
            equipmentCV.wait(lock);
        }
    } while (found == nullptr);

    equipmentCV.notify_one();
    return found;
}


