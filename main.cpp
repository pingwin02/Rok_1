#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "wazne.h"
#include "player.h"
#include "state.h"



int main() {
    char komenda[MAX_DLUGOSC_KOMENDY]; //tablica komend
    int szerokosc = SZER_PLANSZY;
    int wysokosc = WYS_PLANSZY;
    int* width = &szerokosc;
    int* height = &wysokosc;

    //limit uzycia MOVE podczas kolejki {ile max,ile uzyto} {CAR,BAT,CRU,DES}
    int ruch[4][2] = {{MAX_MOVE_CAR,0},{MAX_MOVE_OTHER,0},{MAX_MOVE_OTHER,0},{MAX_MOVE_OTHER,0}};

    const char state[] = "[state]";

    //{x1A,x1B}{y1A,y1B}{x2A,x2B}{y2A,y2B}

    int init_positions[4][2] = { {0,0}, {0,*height / 2 + 1},{*width - 1,*width - 1},{*height / 2 - 1,*height - 1} };

    const char playerA[] = "[playerA]";
    const char playerB[] = "[playerB]";

    char** plansza = stworztablice(*height, *width); //plansza[wiersze][kolumny]
    int wygrana = 0; //flaga wygranej
    int ifjustclosedX = 01; //01-teraz kolej A, 10-teraz kolej B
    int* ijcX = &ifjustclosedX;

    int exships = 0; //flaga trybu extended_ships, domyslnie wylaczona
    int* extended_ships = &exships;

    do {
        scanf("%49s", komenda);

        if (std::cin.peek() == EOF) //jesli koniec pliku zatrzymaj program
            return 0;

        if (czykomenda(komenda, playerA)) { //komendy dla gracza [playerA]
            player(width, height, komenda, plansza, ifjustclosedX, 'A', playerA, playerB, init_positions,ruch, extended_ships);
            ifjustclosedX = 10;
        }
        else if (czykomenda(komenda, playerB)) { //komendy dla gracza [playerB]
            player(width, height, komenda, plansza, ifjustclosedX, 'B', playerB, playerA, init_positions,ruch, extended_ships);
            ifjustclosedX = 01;
        }
        else if (czykomenda(komenda, state)) { //komendy dla [state]
            plansza=fstate(width, height, komenda, plansza, ijcX, init_positions, extended_ships);
        }
        else if (czykomenda(komenda, state) == 0 && czykomenda(komenda, playerA) == 0 && czykomenda(komenda, playerB) == 0) { //gdy komenda jest niezgodna
            printf("INVALID OPERATION \"%s\": [state] OR [playerx] EXPECTED", komenda);
            exit(0);
        }
        if (czywszystkiestatki() == 0&&czyzaczeto()) {
                wygrana = sprawdzaj_stan(); //sprawdzaj stan gry dopiero po ustawieniu wszystkich statkow i zaczeciu gry
        };
    } while (wygrana == 0); //wykonuj dopoki nikt nie wygral
    if (wygrana == 1)  printf("A won\n");
    else if (wygrana == 2)  printf("B won\n");
    for (int i = 0; i < *height; i++) //zwolnienie pamieci, usuniecie tablicy
    {
        delete[] plansza[i];
    }
    delete[] plansza;
    return 0;

}