#ifndef SO2_PROJ_CLIENT_H
#define SO2_PROJ_CLIENT_H
#include "Order.h"
#include "Kitchen.h"
#include <memory>

class Client {
    void threadFunction(const std::shared_ptr<Kitchen> &kitchen, const Menu& menu);
    std::thread thread;
    int ordersInterval;
public:
    Client(const std::shared_ptr<Kitchen> &kitchen, const Menu &menu, int orderInterval);
    void start();
};


#endif
