#ifndef SO2_PROJ_COOK_H
#define SO2_PROJ_COOK_H
#include <memory>
#include "Order.h"
#include "Kitchen.h"

class Cook {
    static int ID;
    void threadFunction(const std::shared_ptr<Kitchen> &kitchen);
    long id;
    std::shared_ptr<Order> order = nullptr;
    std::thread thread;

public:
    Cook(const std::shared_ptr<Kitchen> &kitchen);
    void start();

};


#endif
