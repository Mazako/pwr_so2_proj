#ifndef SO2_PROJ_CLIENT_H
#define SO2_PROJ_CLIENT_H
#include "Order.h"
#include "Kitchen.h"
#include <memory>

class Client {
    static long ID;
    long id;
    void threadFunction(const std::shared_ptr<Kitchen> &kitchen, const Menu& menu);
    std::thread thread;

public:
    Client(const std::shared_ptr<Kitchen> &kitchen, const Menu& menu);
    void start();
};


#endif
