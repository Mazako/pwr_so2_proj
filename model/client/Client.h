#ifndef SO2_PROJ_CLIENT_H
#define SO2_PROJ_CLIENT_H
#include "Order.h"
#include <memory>

class Client {
    long id;
public:
    std::shared_ptr<Order> orderRandomMeal();
};


#endif
