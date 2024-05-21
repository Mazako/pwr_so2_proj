#ifndef SO2_PROJ_ORDER_H
#define SO2_PROJ_ORDER_H

#include <atomic>
#include "Meal.h"

class Order {
    static long ID;
    long id;
    Meal meal;

public:
    Order(Meal meal);

    long getId() const;

    const Meal &getMeal() const;
};


#endif
