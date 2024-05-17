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
    Cook(const std::shared_ptr<Kitchen> &kitchen, int x1, int y1, int x2, int y2, std::string letter) : MakeMove(x1,y1,x2,y1,letter);
    void start();

};


#endif
