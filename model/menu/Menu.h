#ifndef SO2_PROJ_MENU_H
#define SO2_PROJ_MENU_H
#include <vector>
#include <memory>
#include "Meal.h"
#include "Order.h"
class Menu {
    std::vector<Meal> meals;
public:
    Menu();
    std::shared_ptr<Order> createRandomOrder(long clientId) const;
};




#endif //SO2_PROJ_MENU_H
