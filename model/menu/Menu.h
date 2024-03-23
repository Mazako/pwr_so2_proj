#ifndef SO2_PROJ_MENU_H
#define SO2_PROJ_MENU_H
#include <vector>
#include <memory>
#include "Meal.h"

class Menu {
    std::vector<std::shared_ptr<Meal>> meals;
};


#endif //SO2_PROJ_MENU_H
