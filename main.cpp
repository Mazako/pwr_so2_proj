#include <iostream>
#include <ncurses.h>
#include <thread>
#include "KitchenEquipment.h"
#include "Waiter.h"
#include "Kitchen.h"
#include "Cook.h"
#include "model/client/Client.h"


// (G) - GOTOWANIE
// (D) - DOSTAWA
// (S) - SPRZĘT

void cursesDemo() {
    initscr();
    printw("Hello World! Press any key to exit ...");
    refresh();
    getch();
    endwin();
}

void simulation() {
    auto kitchen = std::make_shared<Kitchen>();
    auto menu = Menu();

    auto clientThread = std::make_unique<Client>(kitchen, menu);
    auto cook1 = std::make_unique<Cook>(kitchen);
    auto cook2 = std::make_unique<Cook>(kitchen);
    auto waiter1 = std::make_unique<Waiter>(kitchen);
    auto waiter2 = std::make_unique<Waiter>(kitchen);

    cook1->start();
    cook2->start();
    waiter1->start();
    waiter2->start();
    clientThread->start();
}

int main() {
    cursesDemo();
}
