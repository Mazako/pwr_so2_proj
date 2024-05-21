//
// Created by apox on 5/21/24.
//

#ifndef SO2_PROJ_SETUPMENU_H
#define SO2_PROJ_SETUPMENU_H

#include <ncurses.h>
#include <iostream>


class SetupMenu {
    int *cooks ;
    int *waiters;
    int *ordersInterval;
    int *breakdownInterval;

public:
    SetupMenu(int *cooks, int *waiters, int *ordersInterval, int *breakdownInterval);
    void setCooks();
    void setWaiters();
    void setOrdersInterval();
    void setBreakdownInterval();
    void displayMenu();

};


#endif //SO2_PROJ_SETUPMENU_H
