#ifndef SO2_PROJ_KITCHENEQUIPMENT_H
#define SO2_PROJ_KITCHENEQUIPMENT_H
#include <string>
#include <atomic>
#include <condition_variable>
#include <vector>
#include "EquipmentType.h"
#include <functional>

class KitchenEquipment {
public:
    KitchenEquipment(EquipmentType type, int y);
    bool use(long time,
             std::function<void(int)> xSetter,
             std::function<void(int)> ySetter,
             std::function<void(void)> basicYReset,
             std::function<void(EquipmentType)> kitchenEqSetter);
    bool isBusy();

    void setBroken(bool b);

    bool isBroken() const;

    long getId() const;

private:

    bool broken;
    static long ID;
    int y;
    mutable std::mutex mutex;
    EquipmentType type;
    long id;

    std::condition_variable cv;
public:
    int getY() const;

    EquipmentType getType() const;
    void notifyAll();

private:
    bool busy = false;
};




#endif
