#include <iostream>
#include <ncurses.h>
#include <thread>
#include <random>
#include "Waiter.h"
#include "Kitchen.h"
#include "Cook.h"
#include "model/client/Client.h"
#include "model/setup_menu/SetupMenu.h"


// (G) - GOTOWANIE
// (D) - DOSTAWA
// (S) - SPRZĘT

int NUMS_OF_COOKS =1;
int NUMS_OF_WAITERS=1;
int ORDERS_INTERVAL=1000;
int BREAKDOWN_INTERVAL=10000;

int getRandomBreakTime(int start, int end) {
    std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<> distribution(start, end);
    return distribution(rng);
}


const char *equipmentTypeToString(EquipmentType type) {
    switch (type) {
        case EquipmentType::OVEN:
            return "Oven";
        case EquipmentType::MIXER:
            return "Mixer";
        case EquipmentType::COOKER:
            return "Cooker";
        case EquipmentType::PAN:
            return "Pan";
        case EquipmentType::MICROVAVE:
            return "Microwave";
        case EquipmentType::TABLE:
            return "Table";
        default:
            return "Unknown";
    }
}

void rectangle(int y1, int x1, int y2, int x2) {
    mvhline(y1, x1, 0, x2 - x1);
    mvhline(y2, x1, 0, x2 - x1);
    mvvline(y1, x1, 0, y2 - y1);
    mvvline(y1, x2, 0, y2 - y1);
    mvaddch(y1, x1, ACS_ULCORNER);
    mvaddch(y2, x1, ACS_LLCORNER);
    mvaddch(y1, x2, ACS_URCORNER);
    mvaddch(y2, x2, ACS_LRCORNER);
}


void addCook(std::vector<std::shared_ptr<Cook>> &cooks, std::shared_ptr<Kitchen> &kitchen) {
    int size = cooks.size();
    if (size > 14) {
        return;
    }
    cooks.push_back(std::make_shared<Cook>(kitchen,
                                           30,
                                           1 + size,
                                           ("C" + std::to_string(size + 1))));
}

void addWaiter(std::vector<std::shared_ptr<Waiter>> &waiters, std::shared_ptr<Kitchen> &kitchen) {
    int size = waiters.size();
    if (size > 14) {
        return;
    }
    waiters.push_back(std::make_shared<Waiter>(kitchen,
                                               100,
                                               1 + size,
                                               ("W" + std::to_string(size + 1))));
}

void cursesDraw(std::vector<std::shared_ptr<Cook>> &cooks,
                std::vector<std::shared_ptr<Waiter>> &waiters,
                std::shared_ptr<Kitchen> &kitchen) {
    initscr();
    noecho();
    curs_set(FALSE);
    nodelay(stdscr, TRUE);

    bool simulation = true;

    while (simulation) {
        clear();

        rectangle(0, 50, 11, 80);


        auto waiting = kitchen->getWaitingOrders();

        for (int i = 0; i < waiting.size(); i++) {
            int _x = 51 + (i / 10) * 3;
            mvaddstr((i % 10) + 1, _x, std::to_string(waiting[i]->getId()).c_str());
        }

        auto ready = kitchen->getReadyOrders();

        for (int i = 0; i < ready.size(); i++) {
            int _x = 75 - (i / 10) * 3;
            mvaddstr((i % 10) + 1, _x, std::to_string(ready[i]->getId()).c_str());
        }


        for (const auto &eq: kitchen->getEquipment()) {
            for (const auto &item: eq.second) {
                mvaddstr(item->getY(), 1, equipmentTypeToString(item->getType()));
            }
        }

        for (int i = 0; i < cooks.size(); i++) {
            auto currentCook = cooks[i];
            mvaddstr(18 + i, 1, currentCook->getOrderInfo().c_str());
            mvaddstr(currentCook->getY(), currentCook->getX(), currentCook->getLetter().c_str());
        }

        for (int i = 0; i < waiters.size(); i++) {
            auto currentWaiter = waiters[i];
            mvaddstr(18 + i, 30, currentWaiter->getOrderInfo().c_str());
            mvaddstr(currentWaiter->getY(), currentWaiter->getX(), currentWaiter->getLetter().c_str());
        }

        if (kitchen->isBroken()) {
            mvaddstr(16, 1, "AAAAWARIA PRADU");
        }

        refresh();
        char ch = getch();
        if (ch == 'q') {
            simulation = false;
        } else if (ch == 'c') {
            addCook(cooks, kitchen);
        } else if (ch == 'w') {
            addWaiter(waiters, kitchen);
        }
        napms(100);

    }
    endwin();
    exit(0);
}

void kitchenBreakThread(std::shared_ptr<Kitchen> &kitchen) {
    while (true) {
        int time = getRandomBreakTime(5, 15);
        std::this_thread::sleep_for(std::chrono::seconds(time));
        kitchen->breakEverything();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        kitchen->fixEverything();
        std::this_thread::sleep_for(std::chrono::milliseconds(BREAKDOWN_INTERVAL));
    }
}

void simulation(int cooks, int waiters, int ordersInterval) {
    auto kitchen = std::make_shared<Kitchen>();
    auto menu = Menu();

    std::vector<std::shared_ptr<Cook>> cooksVec;
    std::vector<std::shared_ptr<Waiter>> waitersVec;

    cooksVec.reserve(cooks);
    for (int i = 0; i < cooks; i++) {
        cooksVec.push_back(std::make_shared<Cook>(kitchen,
                                                  30,
                                                  1 + i,
                                                  ("C" + std::to_string(i + 1))));
    }

    waitersVec.reserve(waiters);
    for (int i = 0; i < waiters; i++) {
        waitersVec.push_back(std::make_shared<Waiter>(kitchen,
                                                      100,
                                                      1 + i,
                                                      ("W" + std::to_string(i + 1))));
    }

    auto clientThread = std::make_unique<Client>(kitchen, menu, ordersInterval);
    std::thread cursesDrawThread(cursesDraw,
                                 std::ref(cooksVec),
                                 std::ref(waitersVec),
                                 std::ref(kitchen));

    std::thread breakingThread(kitchenBreakThread, std::ref(kitchen));

    for (const auto &item: cooksVec) {
        item->start();
    }

    for (const auto &item: waitersVec) {
        item->start();
    }

    clientThread->start();
    breakingThread.join();
    cursesDrawThread.join();

}

int main() {
    SetupMenu setupMenu(&NUMS_OF_COOKS, &NUMS_OF_WAITERS, &ORDERS_INTERVAL, &BREAKDOWN_INTERVAL);
    setupMenu.displayMenu();
    simulation(NUMS_OF_COOKS, NUMS_OF_WAITERS, ORDERS_INTERVAL);
}
