#ifndef SO2_PROJ_COOK_H
#define SO2_PROJ_COOK_H
#include "memory"
#include "Order.h"
class Cook {
    long id;
    std::shared_ptr<Order> order = nullptr;
};


#endif
