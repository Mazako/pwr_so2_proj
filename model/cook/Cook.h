#ifndef SO2_PROJ_COOK_H
#define SO2_PROJ_COOK_H
#include <memory>
#include "Order.h"
#include "Kitchen.h"
#include "MakeMove.h"


class Cook : public MakeMove{
    static int ID;
    void threadFunction(const std::shared_ptr<Kitchen> &kitchen);
    long id;
    std::shared_ptr<Order> order = nullptr;
    std::thread thread;

public:
    Cook(const std::shared_ptr<Kitchen> &kitchen, int x1, int y1, const char* letter);
    void start();
    const std::string getOrderInfo();
};


#endif
