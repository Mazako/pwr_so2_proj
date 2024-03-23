#ifndef SO2_PROJ_ORDER_H
#define SO2_PROJ_ORDER_H

#include <atomic>
#include "Meal.h"
#include "OrderStatus.h"

class Order {
    long clientId;
    Meal& meal;
    std::atomic<OrderStatus> status;
};


#endif
