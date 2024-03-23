#ifndef SO2_PROJ_KITCHENEQUIPMENT_H
#define SO2_PROJ_KITCHENEQUIPMENT_H
#include <string>
#include <atomic>
#include "EquipmentType.h"

class KitchenEquipment {
    EquipmentType type;
    std::string name;
    long id;
    std::atomic<bool> busy;

};


#endif
