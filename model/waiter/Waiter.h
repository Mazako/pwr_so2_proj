#ifndef SO2_PROJ_WAITER_H
#define SO2_PROJ_WAITER_H
#include <memory>
#include "Order.h"


class Waiter {
    std::shared_ptr<Order> order = nullptr;
public:
    static const int DELIVERY_TIME_SECONDS = 5;
};


#endif
