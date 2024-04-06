#ifndef SO2_PROJ_KITCHEN_H
#define SO2_PROJ_KITCHEN_H
#include<map>
#include<vector>
#include <queue>
#include <memory>
#include "KitchenEquipment.h"
#include "EquipmentType.h"
#include "Order.h"
#include "Menu.h"

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

public:
    Kitchen();
    std::shared_ptr<KitchenEquipment> getKitchenEquipment(EquipmentType equipmentType);

    void addWaitingOrder(const std::shared_ptr<Order> &order);
    std::shared_ptr<Order> getWaitingOrder();

    void addReadyOrder(const std::shared_ptr<Order> &order);
    std::shared_ptr<Order> getReadyOrder();
};


#endif
