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
int direction = 1; // 1: w prawo, -1: w lewo
int x = 0;

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
            return "Unknown Equipment";
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

void cursesDemo() {    // Inicjalizacja ncurses
    initscr();
    noecho();
    curs_set(FALSE);


    while (1) {
        clear();

        x += direction;

        rectangle(0, 80, 10, 120);

        mvaddch(1, x, 'C');

        refresh(); // Odświeżenie ekranu

        if (x >= 80 - 1 || x <= 0) {
            direction = -direction; // Zmiana kierunku
        }
        usleep(100000); // Opóźnienie 100 ms

    }
    // Czekanie na naciśnięcie klawisza
    getch();
    getch();

    // Zakończenie NCURSES
    endwin();

}

void cursesDraw(std::shared_ptr<Cook> &cook1,
                std::shared_ptr<Cook> &cook2,
                std::shared_ptr<Waiter> &waiter1,
                std::shared_ptr<Waiter> &waiter2,
                std::shared_ptr<Kitchen> &kitchen) {
    initscr();
    noecho();
    curs_set(FALSE);


    while (1) {
        clear();

        rectangle(0, 50, 11, 80);

        mvaddstr(16, 1, cook1->getOrderInfo().c_str());
        mvaddstr(18, 1, cook2->getOrderInfo().c_str());

        for (const auto &eq: kitchen->getEquipment()) {
            for (const auto &item: eq.second) {
                mvaddstr(item->getY(), 1, equipmentTypeToString(item->getType()));
            }
        }

        mvaddstr(cook1->getY(), cook1->getX(), cook1->getLetter());
        mvaddstr(cook1->getY(), cook1->getX(), cook1->getLetter());

        mvaddstr(cook1->getY(), cook1->getX(), cook1->getLetter());
        mvaddstr(cook2->getY(), cook2->getX(), cook2->getLetter());

        refresh();

        usleep(100000); // Opóźnienie 100 ms

    }

    // Czekanie na naciśnięcie klawisza
    getch();
    getch();

    // Zakończenie NCURSES
    endwin();
}

void simulation() {
    auto kitchen = std::make_shared<Kitchen>();
    auto menu = Menu();

    auto clientThread = std::make_unique<Client>(kitchen, menu);
    auto cook1 = std::make_shared<Cook>(kitchen, 30, 5, "C1");
    auto cook2 = std::make_shared<Cook>(kitchen, 30, 7, "C2");
    auto waiter1 = std::make_shared<Waiter>(kitchen);
    auto waiter2 = std::make_shared<Waiter>(kitchen);
    std::thread cursesDrawThread(cursesDraw,
                                 std::ref(cook1),
                                 std::ref(cook2),
                                 std::ref(waiter1),
                                 std::ref(waiter2),
                                 std::ref(kitchen));

    cook1->start();
    cook2->start();
    waiter1->start();
    waiter2->start();
    clientThread->start();
    cursesDrawThread.join();
}

int main() {
    simulation();
}
