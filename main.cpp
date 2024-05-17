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

void cursesDemo() {    // Inicjalizacja ncurses
    initscr();             // Przełącz do trybu ncurses
    cbreak();              // Linie wejściowe są przekazywane do bufora, bez buforowania
    noecho();              // Nie wyświetlaj wpisywanych znaków
    keypad(stdscr, TRUE);  // Włącz obsługę klawiszy funkcyjnych i strzałek

    // Deklaracja opcji do wyświetlenia
    std::vector<std::string> options = {"Opcja 1", "Opcja 2", "Opcja 3", "Wyjście"};

    int choice;
    int highlight = 0;

    while (true) {
        // Wypisywanie wszystkich opcji, wyróżnienie wybranej
        for (int i = 0; i < options.size(); ++i) {
            if (i == highlight) {
                attron(A_REVERSE);  // Odwróć kolor dla wyróżnienia
            }
            mvprintw(i, 0, options[i].c_str());
            if (i == highlight) {
                attroff(A_REVERSE);
            }
        }

        // Odczytanie klawisza od użytkownika
        choice = getch();

        // Poruszanie się po opcjach
        switch (choice) {
        case KEY_UP:
            if (highlight > 0) {
                --highlight;
            }
            break;
        case KEY_DOWN:
            if (highlight < options.size() - 1) {
                ++highlight;
            }
            break;
        default:
            break;
        }

        // Jeśli wciśnięto Enter, zakończ pętlę
        if (choice == 10) {  // 10 to kod klawisza Enter
            break;
        }
    }

    // Czyszczenie ekranu
    clear();

    // Wyświetlenie wybranej opcji
    if (highlight == options.size() - 1) {
        printw("Zakończenie programu...");
    } else {
        printw("Wybrano: %s", options[highlight].c_str());
    }

    // Oczekiwanie na naciśnięcie dowolnego klawisza przed wyjściem
    getch();

    // Zakończenie pracy z ncurses
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
