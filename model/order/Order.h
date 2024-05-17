#ifndef SO2_PROJ_ORDER_H
#define SO2_PROJ_ORDER_H

#include <atomic>
#include "Meal.h"
#include "OrderStatus.h"

class Order {
    static long ID;
    long id;
    long clientId;
    Meal meal;
    std::atomic<OrderStatus> status;
public:
    long getClientId() const;

    const std::atomic<OrderStatus> &getStatus() const;

public:
    Order(long clientId, Meal meal);
    ~Order();

    long getId() const;

    const Meal &getMeal() const;
};


#endif
