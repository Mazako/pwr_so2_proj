//
// Created by apox on 5/21/24.
//

#include "SetupMenu.h"
#include <ncurses.h>
#include <iostream>


void SetupMenu::displayMenu() {
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1, COLOR_RED, COLOR_GREEN);


    bool inMenu = true;
    while (inMenu) {
        clear();
        mvprintw(1, 1, "USTAWIENIA ( DOMYSLNE: KUCHARZE: 1, KELNERZY: 1, CZAS POMIEDZY ZAMOWIENIAMI: 1S, CZAS DO KOLEJNEJ AWARI: 10)");
        mvprintw(3, 1, "1. Ilosc kucharzy");
        mvprintw(4, 1, "2. Ilosc kelnerow");
        mvprintw(5, 1, "3. Czas pomiedzy zamowieniami" );
        mvprintw(6, 1, "4. Czas do kolejnej awari");

        mvprintw(8, 1, "S - start");
        refresh();

        char ch = getch();
        switch (ch) {
            case '1':
                setCooks();
                break;
            case '2':
                setWaiters();
                break;
            case '3':
                setOrdersInterval();
                break;
            case '4':
                setBreakdownInterval();
                break;
            case 's':
                inMenu = false;

        }
    }
    endwin();

}

void SetupMenu::setCooks() {
    bool goBack = false;
    while (!goBack) {
        clear();
        mvprintw(1, 1, "Zwieksz '+' : +1 , Zmniejsz '-': -1");
        std::string cooksInfo = "Ilosc kucharzy: " + std::to_string(*cooks);
        mvaddstr(2, 1, cooksInfo.c_str());
        mvprintw(3, 1, "Powrot i zapis: 'b'");
        char ch = getch();
        if (ch == '=' && (*cooks) <=15){
            (*cooks)++;
        }
        if (ch == '-'  && (*cooks) >0){
            (*cooks)--;
        }
        if (ch == 'b'){
            goBack= true;
        }
        refresh();
    }
}

void SetupMenu::setWaiters() {
    bool goBack = false;
    while (!goBack) {
        clear();
        mvprintw(1, 1, "Zwieksz '+' : +1 , Zmniejsz '-': -1");
        std::string cooksInfo = "Ilosc kelnerow: " + std::to_string(*waiters);
        mvaddstr(2, 1, cooksInfo.c_str());
        mvprintw(3, 1, "Powrot i zapis: 'b'");
        char ch = getch();
        if (ch == '=' && (*waiters) <=15){
            (*waiters)++;
        }
        if (ch == '-'  && (*waiters) >0){
            (*waiters)--;
        }
        if (ch == 'b'){
            goBack= true;
        }
        refresh();
    }
}

void SetupMenu::setOrdersInterval() {
    bool goBack = false;
    while (!goBack) {
        clear();
        mvprintw(1, 1, "Zwieksz '+' : +100 ms , Zmniejsz '-': -100 ms");
        std::string cooksInfo = "Czas pomiedzy zamowieniami: " + std::to_string(*ordersInterval);
        mvaddstr(2, 1, cooksInfo.c_str());
        mvprintw(3, 1, "Powrot i zapis: 'b'");
        char ch = getch();
        if (ch == '='){
            (*ordersInterval)+=100;
        }
        if (ch == '-'  && (*ordersInterval) >100){
            (*ordersInterval)-=100;
        }
        if (ch == 'b'){
            goBack= true;
        }
        refresh();
    }
}

void SetupMenu::setBreakdownInterval() {
    bool goBack = false;
    while (!goBack) {
        clear();
        mvprintw(1, 1, "Zwieksz '+' : +1000 ms , Zmniejsz '-': -1000 ms");
        std::string cooksInfo = "Minimalny czas pomiedzy awarami: " + std::to_string(*breakdownInterval);
        mvaddstr(2, 1, cooksInfo.c_str());
        mvprintw(3, 1, "Powrot i zapis: 'b'");
        char ch = getch();
        if (ch == '='){
            (*breakdownInterval)+=1000;
        }
        if (ch == '-'  && (*breakdownInterval) >1000){
            (*breakdownInterval)-=1000;
        }
        if (ch == 'b'){
            goBack= true;
        }
        refresh();
    }
}

SetupMenu::SetupMenu(int *cooks, int *waiters, int *ordersInterval, int *breakdownInterval) {
    this->cooks=cooks;
    this->waiters=waiters;
    this->ordersInterval=ordersInterval;
    this->breakdownInterval=breakdownInterval;
}
