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
             std::function<void(void)> basicYReset);
    void setBroken(bool b);


private:

    bool broken = false;
    int y;
    mutable std::mutex mutex;
    EquipmentType type;

    std::condition_variable cv;
public:
    int getY() const;

    EquipmentType getType() const;
    void notifyAll();

private:
    bool busy = false;
};




#endif
