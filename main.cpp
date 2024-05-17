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

void rectangle(int y1, int x1, int y2, int x2)
{
    mvhline(y1, x1, 0, x2-x1);
    mvhline(y2, x1, 0, x2-x1);
    mvvline(y1, x1, 0, y2-y1);
    mvvline(y1, x2, 0, y2-y1);
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

        rectangle(0,80,10,120);

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

void simulation() {
    auto kitchen = std::make_shared<Kitchen>();
    auto menu = Menu();

    auto clientThread = std::make_unique<Client>(kitchen, menu);
    auto cook1 = std::make_unique<Cook>(kitchen, 1, 1, 79, 12, "C1");
    auto cook2 = std::make_unique<Cook>(kitchen, 1, 3, 79, 15, "C2");
    auto waiter1 = std::make_unique<Waiter>(kitchen);
    auto waiter2 = std::make_unique<Waiter>(kitchen);

    

    cook1->start();
    cook2->start();
    waiter1->start();
    waiter2->start();
    clientThread->start();

    // Start drawing
    initscr();
    noecho();
    curs_set(FALSE);

    while (1) {
        clear();

        x += direction;

        rectangle(0,80,10,120);

        mvaddstr(cook1->getY1(), cook1->getX1(), cook1->getLetter());
        
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

int main() {
    cursesDemo();
}
