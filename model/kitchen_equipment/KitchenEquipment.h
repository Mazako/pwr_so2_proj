#ifndef SO2_PROJ_KITCHENEQUIPMENT_H
#define SO2_PROJ_KITCHENEQUIPMENT_H
#include <string>
#include <atomic>
#include <condition_variable>
#include <vector>
#include "EquipmentType.h"

class KitchenEquipment {
public:
    KitchenEquipment(EquipmentType type, int y);
    void use(long time, long ids);
    bool isBusy();


    long getId() const;

private:
    static long ID;
    int y;
    mutable std::mutex mutex;
    EquipmentType type;
    long id;

    std::condition_variable cv;
public:
    int getY() const;

    EquipmentType getType() const;

private:
    std::atomic<bool> busy = false;
};




#endif
