#include <iostream>
#include "drukowanie.h"

using namespace std;

void drukuj(char plansza[][3 * WIDTH]) { //drukuj plansze
    for (int i = HEIGHT; i < 2 * HEIGHT; i++) {
        for (int j = WIDTH; j < 2 * WIDTH; j++)
            cout << plansza[i][j];
        cout << endl;
    }
}
