#ifndef SO2_PROJ_KITCHEN_H
#define SO2_PROJ_KITCHEN_H
#include<map>
#include<vector>
#include <queue>
#include <memory>
#include "EquipmentType.h"
#include "Order.h"
#include "Menu.h"
#include "KitchenEquipment.h"

class Kitchen {
    std::map<EquipmentType, std::vector<std::shared_ptr<KitchenEquipment>>> equipment;
    std::mutex equipmentMutex;
    std::condition_variable equipmentCV;

    std::deque<std::shared_ptr<Order>> waitingOrders;
    std::mutex waitingOrdersMutex;
    std::condition_variable waitingOrdersCV;

    std::deque<std::shared_ptr<Order>> readyOrders;
    std::mutex readyOrdersMutex;
    std::condition_variable readyOrdersCV;

    bool broken;

public:
    bool isBroken() const;

public:
    Kitchen();
    std::shared_ptr<KitchenEquipment> getKitchenEquipment(EquipmentType equipmentType);

    void addWaitingOrder(const std::shared_ptr<Order> &order);
    std::shared_ptr<Order> getWaitingOrder();

    void addReadyOrder(const std::shared_ptr<Order> &order);
    std::shared_ptr<Order> getReadyOrder();

    const std::map<EquipmentType, std::vector<std::shared_ptr<KitchenEquipment>>> &getEquipment() const;

    const std::deque<std::shared_ptr<Order>> &getWaitingOrders() const;

    const std::deque<std::shared_ptr<Order>> &getReadyOrders() const;

    void breakEverything();
    void fixEverything();
};


#endif
