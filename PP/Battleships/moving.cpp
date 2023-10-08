#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "wazne.h"
#include "moving.h"


void fmove(char kto, char** plansza, int* width, int* height, int ruch[][2], int* extended_ships) {

    int id, typ = 0;
    int dodaj = 0;
    char klasa[4]{};
    char droga;

    const char car[] = "CAR"; //dlugosc 5
    const char bat[] = "BAT"; //dlugosc 4
    const char cru[] = "CRU"; //dlugosc 3
    const char des[] = "DES"; //dlugosc 2

    std::cin >> id;

    scanf("%3s", klasa);

    std::cin >> droga;

    if (czywszystkiestatki() == 404) { //walidacja statkow na mapie, nie mozna uzyc MOVE gdy nie ma ich wszystkich
        printf("INVALID OPERATION \"MOVE %d %s %c\": NOT ALL SHIPS PLACED", id, klasa, droga);
        exit(0);
    }
    if (czykomenda(klasa, car)) {
        ruch[0][1]++;
        typ = DLUGOSC_CAR;
        dodaj = 0;
        if (*extended_ships == 1) {//dla extended_ships gdy statek ma zniszczony silnik, nie moze sie poruszac
            if ((kto == 'A' && statekA.silnik[id + dodaj] == 1) || (kto == 'B' && statekB.silnik[id + dodaj] == 1)) {
                printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE", id, klasa, droga);
                exit(0);
            }

        }
        if (ruch[0][1] > ruch[0][0]) {//walidacja ilosci ruchu
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY", id, klasa, droga);
            exit(0);
        }

    }
    if (czykomenda(klasa, bat)) {
        ruch[1][1]++;
        typ = DLUGOSC_BAT;
        dodaj = 10;
        if (*extended_ships == 1) {
            if ((kto == 'A' && statekA.silnik[id + dodaj] == 1) || (kto == 'B' && statekB.silnik[id + dodaj] == 1)) {
                printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE", id, klasa, droga);
                exit(0);
            }
        }
        if (ruch[1][1] > ruch[1][0]) {
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY", id, klasa, droga);
            exit(0);
        }
    }
    if (czykomenda(klasa, cru)) {
        ruch[2][1]++;
        typ = DLUGOSC_CRU;
        dodaj = 20;
        if (*extended_ships == 1) {
            if ((kto == 'A' && statekA.silnik[id + dodaj] == 1) || (kto == 'B' && statekB.silnik[id + dodaj] == 1)) {
                printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE", id, klasa, droga);
                exit(0);
            }
        }
        if (ruch[2][1] > ruch[2][0]) {
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY", id, klasa, droga);
            exit(0);
        }
    }
    if (czykomenda(klasa, des)) {
        ruch[3][1]++;
        typ = DLUGOSC_DES;
        dodaj = 30;
        if (*extended_ships == 1) {
            if ((kto == 'A' && statekA.silnik[id + dodaj] == 1) || (kto == 'B' && statekB.silnik[id + dodaj] == 1)) {
                printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP CANNOT MOVE", id, klasa, droga);
                exit(0);
            }

        }
        if (ruch[3][1] > ruch[3][0]) {
            printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP MOVED ALREADY", id, klasa, droga);
            exit(0);
        }
    }
    //jesli statek o podanym id i klasie nie istnieje
    if ((kto == 'A' && statekA.id[id + dodaj] == 0) || (kto == 'B' && statekB.id[id + dodaj] == 0))
    {
        printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP NOT FOUND", id, klasa, droga);
        exit(0);
    }
    //funkcja do poruszania statkow
    movingships(kto, id, dodaj, typ, klasa, droga, plansza, width, height);

}

void movingships(char kto, int id, int dodaj, int typ, char* klasa, char droga, char** plansza, int* width, int* height) {

    //dla funkcji czujnik_rafa_statek
    char komenda[] = "MOVE";
    char damage[5] = { '1','1','1','1','1' };

    switch (droga) {
    case 'F': { //poruszanie prosto
        switch (kto) {
        case 'A': {
            switch (statekA.kierunek[id + dodaj]) {
            case 'N': {
                if (statekA.y[id + dodaj] == 0) {//walidacja wyjscia poza plansze
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    //wywolanie funkcji mojswap, podmienia znaki w tablicy, porusza statek
                    mojswap(plansza[statekA.y[id + dodaj] + i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] + i - 1][statekA.x[id + dodaj]], id, klasa, droga);
                //przypisanie do bazy nowych danych o statku
                przypisaniebaza(statekA.y[id + dodaj] - 1, statekA.x[id + dodaj], 'N', klasa, id, kto);
                statekA.silnikY[id + dodaj] -= 1;
                statekA.dzialoY[id + dodaj] -= 1;
                //walidacja rafy i pobliskich statkow
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekA.x[id + dodaj] == *width - 1) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] - i], plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] - i + 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj], statekA.x[id + dodaj] + 1, 'E', klasa, id, kto);
                statekA.silnikX[id + dodaj] += 1;
                statekA.dzialoX[id + dodaj] += 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekA.y[id + dodaj] == *height - 1) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj] - i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] - i + 1][statekA.x[id + dodaj]], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] + 1, statekA.x[id + dodaj], 'S', klasa, id, kto);
                statekA.silnikY[id + dodaj] += 1;
                statekA.dzialoY[id + dodaj] += 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekA.x[id + dodaj] == 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] + i], plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] + i - 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj], statekA.x[id + dodaj] - 1, 'W', klasa, id, kto);
                statekA.silnikX[id + dodaj] -= 1;
                statekA.dzialoX[id + dodaj] -= 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        case 'B': {
            switch (statekB.kierunek[id + dodaj]) {
            case 'N': {
                if (statekB.y[id + dodaj] == 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] + i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] + i - 1][statekB.x[id + dodaj]], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] - 1, statekB.x[id + dodaj], 'N', klasa, id, kto);
                statekB.silnikY[id + dodaj] -= 1;
                statekB.dzialoY[id + dodaj] -= 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekB.x[id + dodaj] == *width - 1) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] - i], plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] - i + 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj], statekB.x[id + dodaj] + 1, 'E', klasa, id, kto);
                statekB.silnikX[id + dodaj] += 1;
                statekB.dzialoX[id + dodaj] += 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekB.y[id + dodaj] == *height - 1) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] - i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] - i + 1][statekB.x[id + dodaj]], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] + 1, statekB.x[id + dodaj], 'S', klasa, id, kto);
                statekB.silnikY[id + dodaj] += 1;
                statekB.dzialoY[id + dodaj] += 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekB.x[id + dodaj] == 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] + i], plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] + i - 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj], statekB.x[id + dodaj] - 1, 'W', klasa, id, kto);
                statekB.silnikX[id + dodaj] -= 1;
                statekB.dzialoX[id + dodaj] -= 1;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        default: exit(0);
        }
        break;
    }
    case 'L': { //poruszanie w lewo
        switch (kto) {
        case 'A': {
            switch (statekA.kierunek[id + dodaj]) {
            case 'N': {
                if (statekA.y[id + dodaj] == 0 || statekA.x[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj] + i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] - 1][statekA.x[id + dodaj] - typ + i + 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] - 1, statekA.x[id + dodaj] - typ + 1, 'W', klasa, id, kto);
                statekA.silnikY[id + dodaj] -= typ;
                statekA.dzialoY[id + dodaj] -= 2;
                statekA.dzialoX[id + dodaj] -= typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekA.x[id + dodaj] == *width - 1 || statekA.y[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] - i], plansza[statekA.y[id + dodaj] - typ + i + 1][statekA.x[id + dodaj] + 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] - typ + 1, statekA.x[id + dodaj] + 1, 'N', klasa, id, kto);
                statekA.silnikX[id + dodaj] += typ;
                statekA.dzialoY[id + dodaj] -= typ - 2;
                statekA.dzialoX[id + dodaj] += 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekA.y[id + dodaj] == *height - 1 || statekA.x[id + dodaj] + typ - 1 >= *width) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj] - i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] + 1][statekA.x[id + dodaj] + typ - i - 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] + 1, statekA.x[id + dodaj] + typ - 1, 'E', klasa, id, kto);
                statekA.silnikY[id + dodaj] += typ;
                statekA.dzialoY[id + dodaj] += 2;
                statekA.dzialoX[id + dodaj] += typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekA.x[id + dodaj] == 0 || statekA.y[id + dodaj] + typ - 1 >= *height) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] + i], plansza[statekA.y[id + dodaj] + typ - i - 1][statekA.x[id + dodaj] - 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] + typ - 1, statekA.x[id + dodaj] - 1, 'S', klasa, id, kto);
                statekA.silnikX[id + dodaj] -= typ;
                statekA.dzialoY[id + dodaj] += typ - 2;
                statekA.dzialoX[id + dodaj] -= 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        case 'B': {
            switch (statekB.kierunek[id + dodaj]) {
            case 'N': {
                if (statekB.y[id + dodaj] == 0 || statekB.x[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] + i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] - 1][statekB.x[id + dodaj] - typ + i + 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] - 1, statekB.x[id + dodaj] - typ + 1, 'W', klasa, id, kto);
                statekB.silnikY[id + dodaj] -= typ;
                statekB.dzialoY[id + dodaj] -= 2;
                statekB.dzialoX[id + dodaj] -= typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekB.x[id + dodaj] == *width - 1 || statekB.y[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] - i], plansza[statekB.y[id + dodaj] - typ + i + 1][statekB.x[id + dodaj] + 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] - typ + 1, statekB.x[id + dodaj] + 1, 'N', klasa, id, kto);
                statekB.silnikX[id + dodaj] += typ;
                statekB.dzialoY[id + dodaj] -= typ - 2;
                statekB.dzialoX[id + dodaj] += 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekB.y[id + dodaj] == *height - 1 || statekB.x[id + dodaj] + typ - 1 >= *width) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] - i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] + 1][statekB.x[id + dodaj] + typ - i - 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] + 1, statekB.x[id + dodaj] + typ - 1, 'E', klasa, id, kto);
                statekB.silnikY[id + dodaj] += typ;
                statekB.dzialoY[id + dodaj] += 2;
                statekB.dzialoX[id + dodaj] += typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekB.x[id + dodaj] == 0 || statekB.y[id + dodaj] + typ - 1 >= *height) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] + i], plansza[statekB.y[id + dodaj] + typ - i - 1][statekB.x[id + dodaj] - 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] + typ - 1, statekB.x[id + dodaj] - 1, 'S', klasa, id, kto);
                statekB.silnikX[id + dodaj] -= typ;
                statekB.dzialoY[id + dodaj] += typ - 2;
                statekB.dzialoX[id + dodaj] -= 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        default: exit(0);
        }
        break;
    }
    case 'R': { //poruszanie w prawo
        switch (kto) {
        case 'A': {
            switch (statekA.kierunek[id + dodaj]) {
            case 'N': {
                if (statekA.y[id + dodaj] == 0 || statekA.x[id + dodaj] + typ - 1 >= *width) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj] + i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] - 1][statekA.x[id + dodaj] + typ - i - 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] - 1, statekA.x[id + dodaj] + typ - 1, 'E', klasa, id, kto);
                statekA.silnikY[id + dodaj] -= typ;
                statekA.dzialoY[id + dodaj] -= 2;
                statekA.dzialoX[id + dodaj] += typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekA.x[id + dodaj] == *width - 1 || statekA.y[id + dodaj] + typ - 1 >= *height) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] - i], plansza[statekA.y[id + dodaj] + typ - i - 1][statekA.x[id + dodaj] + 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] + typ - 1, statekA.x[id + dodaj] + 1, 'S', klasa, id, kto);
                statekA.silnikX[id + dodaj] += typ;
                statekA.dzialoY[id + dodaj] += typ - 2;
                statekA.dzialoX[id + dodaj] += 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekA.y[id + dodaj] == *height - 1 || statekA.x[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj] - i][statekA.x[id + dodaj]], plansza[statekA.y[id + dodaj] + 1][statekA.x[id + dodaj] - typ + i + 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] + 1, statekA.x[id + dodaj] - typ + 1, 'W', klasa, id, kto);
                statekA.silnikY[id + dodaj] += typ;
                statekA.dzialoY[id + dodaj] += 2;
                statekA.dzialoX[id + dodaj] -= typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekA.x[id + dodaj] == 0 || statekA.y[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekA.y[id + dodaj]][statekA.x[id + dodaj] + i], plansza[statekA.y[id + dodaj] - typ + i + 1][statekA.x[id + dodaj] - 1], id, klasa, droga);
                przypisaniebaza(statekA.y[id + dodaj] - typ + 1, statekA.x[id + dodaj] - 1, 'N', klasa, id, kto);
                statekA.silnikX[id + dodaj] -= typ;
                statekA.dzialoY[id + dodaj] -= typ - 2;
                statekA.dzialoX[id + dodaj] -= 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekA.kierunek[id + dodaj], statekA.x[id + dodaj], statekA.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        case 'B': {
            switch (statekB.kierunek[id + dodaj]) {
            case 'N': {
                if (statekB.y[id + dodaj] == 0 || statekB.x[id + dodaj] + typ - 1 >= *width) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] + i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] - 1][statekB.x[id + dodaj] + typ - i - 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] - 1, statekB.x[id + dodaj] + typ - 1, 'E', klasa, id, kto);
                statekB.silnikY[id + dodaj] -= typ;
                statekB.dzialoY[id + dodaj] -= 2;
                statekB.dzialoX[id + dodaj] += typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'E': {
                if (statekB.x[id + dodaj] == *width - 1 || statekB.y[id + dodaj] + typ - 1 >= *height) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] - i], plansza[statekB.y[id + dodaj] + typ - i - 1][statekB.x[id + dodaj] + 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] + typ - 1, statekB.x[id + dodaj] + 1, 'S', klasa, id, kto);
                statekB.silnikX[id + dodaj] += typ;
                statekB.dzialoY[id + dodaj] += typ - 2;
                statekB.dzialoX[id + dodaj] += 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'S': {
                if (statekB.y[id + dodaj] == *height - 1 || statekB.x[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj] - i][statekB.x[id + dodaj]], plansza[statekB.y[id + dodaj] + 1][statekB.x[id + dodaj] - typ + i + 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] + 1, statekB.x[id + dodaj] - typ + 1, 'W', klasa, id, kto);
                statekB.silnikY[id + dodaj] += typ;
                statekB.dzialoY[id + dodaj] += 2;
                statekB.dzialoX[id + dodaj] -= typ - 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            case 'W': {
                if (statekB.x[id + dodaj] == 0 || statekB.y[id + dodaj] - typ + 1 < 0) {
                    printf("INVALID OPERATION \"MOVE %d %s %c\": SHIP WENT FROM BOARD", id, klasa, droga);
                    exit(0);
                }
                for (int i = 0; i < typ; i++)
                    mojswap(plansza[statekB.y[id + dodaj]][statekB.x[id + dodaj] + i], plansza[statekB.y[id + dodaj] - typ + i + 1][statekB.x[id + dodaj] - 1], id, klasa, droga);
                przypisaniebaza(statekB.y[id + dodaj] - typ + 1, statekB.x[id + dodaj] - 1, 'N', klasa, id, kto);
                statekB.silnikX[id + dodaj] -= typ;
                statekB.dzialoY[id + dodaj] -= typ - 2;
                statekB.dzialoX[id + dodaj] -= 2;
                czujnik_rafa_statek(komenda, plansza, typ, statekB.kierunek[id + dodaj], statekB.x[id + dodaj], statekB.y[id + dodaj], id, klasa, width, height, kto, 2, damage, droga);
                break;
            }
            }
            break;
        }
        default: exit(0);
        }
        break;
    }
    default: { //gdy wybrany zostanie zly kierunek ruchu
        printf("INVALID OPERATION \"MOVE %d %s %c\": CHOOSE FROM [F]ORWARD, [L]EFT, [R]IGHT", id, klasa, droga);
        exit(0);
    }

    }

}