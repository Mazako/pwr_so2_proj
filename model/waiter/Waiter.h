#ifndef SO2_PROJ_WAITER_H
#define SO2_PROJ_WAITER_H

#include <thread>
#include <memory>
#include "Order.h"
#include "Kitchen.h"
#include "MakeMove.h"

class Waiter : public MakeMove {
    static int ID;
    int id;
    std::thread thread;
    std::shared_ptr<Order> order;

    void threadFunction(const std::shared_ptr<Kitchen> &kitchen);

public:

    Waiter(const std::shared_ptr<Kitchen> &kitchen, int x, int y, std::string letter);

    void start();

    std::string getOrderInfo();
};

#endif // SO2_PROJ_WAITER_H
