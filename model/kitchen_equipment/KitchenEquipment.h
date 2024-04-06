#ifndef SO2_PROJ_KITCHENEQUIPMENT_H
#define SO2_PROJ_KITCHENEQUIPMENT_H
#include <string>
#include <atomic>
#include <condition_variable>
#include "EquipmentType.h"

class KitchenEquipment {
public:
    KitchenEquipment(EquipmentType type);
    void use(long time, long ids);
    bool isBusy();

    long getId() const;

private:
    static long ID;
    mutable std::mutex mutex;
    EquipmentType type;
    long id;

    std::condition_variable cv;
    std::atomic<bool> busy = false;
};




#endif
