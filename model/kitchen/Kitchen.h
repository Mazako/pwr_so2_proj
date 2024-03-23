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
    //TODO: zasnatowić się czy to dobre rozwiązanie
    std::map<EquipmentType, std::vector<std::shared_ptr<KitchenEquipment>>> equipment;
    std::vector<std::shared_ptr<Order>> orders;

public:
    static const Menu menu;
};


#endif
