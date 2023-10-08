#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "state.h"
#include "wazne.h"
#include "print.h"
#include "player.h"


char** fstate(int* width, int* height, char* komenda, char** plansza, int* ijcX, int init_positions[][2], int* extended_ships) {

    const char print[] = "PRINT";
    const char set_fleet[] = "SET_FLEET";
    const char next_player[] = "NEXT_PLAYER";
    const char save[] = "SAVE";
    const char reef[] = "REEF";
    const char init_position[] = "INIT_POSITION";
    const char state[] = "[state]";
    const char board_size[] = "BOARD_SIZE";
    const char ship[] = "SHIP";
    const char extended_ships_com[] = "EXTENDED_SHIPS";

    do {

        scanf("%49s", komenda);
        if (czykomenda(komenda, print)) { //gdy komenda PRINT
            int x;
            std::cin >> x;
            wydrukuj(width, height, plansza, x, 'C'); //drukuje "nie jako gracz"
        }
        else if (czykomenda(komenda, set_fleet)) { //gdy komenda SET_FLEET
            setfleet();
        }
        else if (czykomenda(komenda, next_player)) { //gdy komenda NEXT_PLAYER
            fnext_player(ijcX);
        }
        else if (czykomenda(komenda, extended_ships_com)) { //gdy komenda EXTENDED_SHIPS
            *extended_ships = 1; //wlacz tryb extended_ships
        }
        else if (czykomenda(komenda, ship)) { //gdy komenda SHIP
            fship(komenda, plansza, width, height, init_positions, extended_ships);
        }
        else if (czykomenda(komenda, board_size)) { //gdy komenda BOARD_SIZE
            if (czyzaczeto() == 1) {
                printf("INVALID OPERATION \"%s\": YOU CANNOT CHANGE SIZE OF BOARD DURING GAME", komenda); //blokada zmiany rozmiaru tablicy
                exit(0);
            }
            plansza = zmienrozmiar(width, height, plansza, init_positions); //wywolanie funkcji zmieniajacej rozmiar planszy
        }
        else if (czykomenda(komenda, init_position)) { //gdy komenda INIT_POSITION
            finit_position(init_positions, width, height);
        }
        else if (czykomenda(komenda, reef)) { //gdy komenda REEF
            wstawianie(width, height, plansza, komenda, '#', 0, 'C', extended_ships); //wstawiam "nie jako gracz"
        }
        else if (czykomenda(komenda, save)) { //gdy komenda SAVE
            fsave(width, height, ijcX, init_positions, extended_ships, plansza);

        }
        else if (czykomenda(komenda, state) == 0) { //gdy nieprawodlowa komenda
            printf("INVALID OPERATION \"%s\": EXPECTED COMMANDS: SET_FLEET, PRINT, NEXT_PLAYER, INIT_POSITON, BOARD_SIZE, REEF, SHIP, EXTENDED_SHIPS, SAVE", komenda);
            exit(0);
        }
    } while (czykomenda(komenda, state) == 0);
    return plansza;
}
void fnext_player(int* ifjustclosedX) { //funkcja NEXT_PLAYER, ustala kolejke
    char kto;
    std::cin >> kto;
    if (kto == 'A') *ifjustclosedX = 01;
    else if (kto == 'B') *ifjustclosedX = 10;
    else {
        printf("INVALID OPERATION \"NEXT_PLAYER %c\": EXPECTED A OR B", kto);
        exit(0);
    }
}
void finit_position(int init_positions[][2], int* width, int* height) { //funkcja INIT_POSITION, ustawia pola startowe graczom
    char kto;
    int x1, y1, x2, y2;
    std::cin >> kto >> y1 >> x1 >> y2 >> x2;
    //walidacja koordynatow
    if (y1<0 || y2<0 || x1<0 || x2<0 || y1>*height || y2>*height || x1>*width || x2>*width)
    {
        printf("INVALID OPERATION \"INIT_POSITION %c %d %d %d %d\": WRONG COORDINATES", kto, y1, x1, y2, x2);
        exit(0);
    }
    if (kto == 'A') {
        init_positions[1][0] = y1;
        init_positions[0][0] = x1;
        init_positions[3][0] = y2;
        init_positions[2][0] = x2;
    }
    else if (kto == 'B') {
        init_positions[1][1] = y1;
        init_positions[0][1] = x1;
        init_positions[3][1] = y2;
        init_positions[2][1] = x2;
    }
    else {
        printf("INVALID OPERATION \"INIT_POSITION %c\": EXPECTED A OR B", kto);
        exit(0);
    }
}
void setfleet() { //funkcja SET_FLEET, ustawia flote graczom
    char kto;
    int a1, a2, a3, a4;
    std::cin >> kto >> a1 >> a2 >> a3 >> a4;
    //walidacja ilosci ustawionej floty
    if (a1 < 0 || a1>MAX_FLEET_SIZE || a2 < 0 || a2>MAX_FLEET_SIZE || a3 < 0 || a3>MAX_FLEET_SIZE || a4 < 0 || a4>MAX_FLEET_SIZE || (a1 == 0 && a2 == 0 && a3 == 0 && a4 == 0)) {
        printf("INVALID OPERATION \"SET_FLEET %c %d %d %d %d\": INVALID FLEET OPTIONS", kto, a1, a2, a3, a4); exit(0);
    }
    switch (kto) {
    case 'A': {statekA.fleet[0][0] = a1; statekA.fleet[1][0] = a2; statekA.fleet[2][0] = a3; statekA.fleet[3][0] = a4; break; }
    case 'B': {statekB.fleet[0][0] = a1; statekB.fleet[1][0] = a2; statekB.fleet[2][0] = a3; statekB.fleet[3][0] = a4; break; }
    default: {printf("INVALID OPERATION \"SET_FLEET %c %d %d %d %d\": PLAYER DOES NOT EXIST", kto, a1, a2, a3, a4); exit(0); }
    }
}
char** zmienrozmiar(int* width, int* height, char** plansza, int init_positions[][2]) {
    int nowadl, nowawys;
    std::cin >> nowawys >> nowadl;
    if (nowawys <= 0 || nowadl <= 0) {
        printf("INVALID OPERATION \"BOARD_SIZE %d %d\": WRONG SIZE", nowawys, nowadl);
        exit(0);
    }
    for (int i = 0; i < *height; i++)//usun stara plansze z pamieci
    {
        delete[] plansza[i];
    }
    delete[] plansza;
    //przypisz nowe rozmiary planszy
    *width = nowadl;
    *height = nowawys;
    char** plansza_nowa = stworznowatablice(nowawys, nowadl);//stworz nowa plansze
    //ustalanie nowych pozycji graczy, gdzie moga klasc statki po zmianie rozmiaru planszy
    init_positions[1][0] = 0; //y1A
    init_positions[0][0] = 0; //x1A
    init_positions[3][0] = nowawys / 2 - 1; //y2A
    init_positions[2][0] = nowadl - 1; //x2A
    init_positions[1][1] = nowawys / 2 + 1; //y1B
    init_positions[0][1] = 0; //x1B
    init_positions[3][1] = nowawys - 1; //y2B
    init_positions[2][1] = nowadl - 1; //x2B

    return plansza_nowa;
}

void fship(char* komenda, char** plansza, int* width, int* height, int init_positions[][2], int* extended_ships) { //funkcja dla SHIP

    char kto;
    std::cin >> kto;

    if (kto == 'A')
        flota(width, height, plansza, komenda, 'A', init_positions, 1, extended_ships);
    else if (kto == 'B')
        flota(width, height, plansza, komenda, 'B', init_positions, 1, extended_ships);
}

void fsave(int* width, int* height, int* ijcX, int init_positions[][2], int* extended_ships, char** plansza) {

    //ustawienia mapy
    printf("[state]\n");
    printf("BOARD_SIZE %d %d \n", *height, *width);
    if (*ijcX == 01)
        printf("NEXT_PLAYER A \n");
    else if (*ijcX == 10)
        printf("NEXT_PLAYER B \n");
    if (*extended_ships == 1)
        printf("EXTENDED_SHIPS\n");

    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            if (plansza[i][j] == '#')
                printf("REEF %d %d \n", i, j);
        }
    }

    int typ = 0;
    //sekcja gracza A
    printf("INIT_POSITION A %d %d %d %d \n", init_positions[1][0], init_positions[0][0], init_positions[3][0], init_positions[2][0]);
    printf("SET_FLEET A %d %d %d %d \n", statekA.fleet[0][0], statekA.fleet[1][0], statekA.fleet[2][0], statekA.fleet[3][0]);
    for (int i = 0; i < 40; i++)
    {
        if (statekA.id[i] != 0)
        {
            if (i < 10) {
                printf("SHIP A %d %d %c %d CAR ", statekA.y[i], statekA.x[i], statekA.kierunek[i], statekA.id[i] - 1);
                typ = DLUGOSC_CAR;
            }
            else if (i < 20) {
                printf("SHIP A %d %d %c %d BAT ", statekA.y[i], statekA.x[i], statekA.kierunek[i], statekA.id[i] - 1);
                typ = DLUGOSC_BAT;

            }
            else if (i < 30) {
                printf("SHIP A %d %d %c %d CRU ", statekA.y[i], statekA.x[i], statekA.kierunek[i], statekA.id[i] - 1);
                typ = DLUGOSC_CRU;
            }
            else {
                printf("SHIP A %d %d %c %d DES ", statekA.y[i], statekA.x[i], statekA.kierunek[i], statekA.id[i] - 1);
                typ = DLUGOSC_DES;
            }

            if (statekA.kierunek[i] == 'N') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekA.y[i] + a][statekA.x[i]] == 'x')
                        printf("0");
                    else if (plansza[statekA.y[i] + a][statekA.x[i]] == '@' || plansza[statekA.y[i] + a][statekA.x[i]] == '%'
                        || plansza[statekA.y[i] + a][statekA.x[i]] == '!' || plansza[statekA.y[i] + a][statekA.x[i]] == '+')
                        printf("1");
                }
            }
            if (statekA.kierunek[i] == 'E') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekA.y[i]][statekA.x[i] - a] == 'x')
                        printf("0");
                    else if (plansza[statekA.y[i]][statekA.x[i] - a] == '@' || plansza[statekA.y[i]][statekA.x[i] - a] == '%'
                        || plansza[statekA.y[i]][statekA.x[i] - a] == '!' || plansza[statekA.y[i]][statekA.x[i] - a] == '+')
                        printf("1");
                }
            }
            if (statekA.kierunek[i] == 'W') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekA.y[i]][statekA.x[i] + a] == 'x')
                        printf("0");
                    else if (plansza[statekA.y[i]][statekA.x[i] + a] == '@' || plansza[statekA.y[i]][statekA.x[i] + a] == '%'
                        || plansza[statekA.y[i]][statekA.x[i] + a] == '!' || plansza[statekA.y[i]][statekA.x[i] + a] == '+')
                        printf("1");
                }
            }
            if (statekA.kierunek[i] == 'S') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekA.y[i] - a][statekA.x[i]] == 'x')
                        printf("0");
                    else if (plansza[statekA.y[i] - a][statekA.x[i]] == '@' || plansza[statekA.y[i] - a][statekA.x[i]] == '%'
                        || plansza[statekA.y[i] - a][statekA.x[i]] == '!' || plansza[statekA.y[i] - a][statekA.x[i]] == '+')
                        printf("1");
                }
            }
            printf("\n");
        }
    }

    //sekcja gracza B
    printf("INIT_POSITION B %d %d %d %d \n", init_positions[1][1], init_positions[0][1], init_positions[3][1], init_positions[2][1]);
    printf("SET_FLEET B %d %d %d %d \n", statekB.fleet[0][0], statekB.fleet[1][0], statekB.fleet[2][0], statekB.fleet[3][0]);
    for (int i = 0; i < 40; i++)
    {
        if (statekB.id[i] != 0)
        {
            if (i < 10) {
                printf("SHIP B %d %d %c %d CAR ", statekB.y[i], statekB.x[i], statekB.kierunek[i], statekB.id[i] - 1);
                typ = DLUGOSC_CAR;
            }
            else if (i < 20) {
                printf("SHIP B %d %d %c %d BAT ", statekB.y[i], statekB.x[i], statekB.kierunek[i], statekB.id[i] - 1);
                typ = DLUGOSC_BAT;

            }
            else if (i < 30) {
                printf("SHIP B %d %d %c %d CRU ", statekB.y[i], statekB.x[i], statekB.kierunek[i], statekB.id[i] - 1);
                typ = DLUGOSC_CRU;
            }
            else {
                printf("SHIP B %d %d %c %d DES ", statekB.y[i], statekB.x[i], statekB.kierunek[i], statekB.id[i] - 1);
                typ = DLUGOSC_DES;
            }

            if (statekB.kierunek[i] == 'N') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekB.y[i] + a][statekB.x[i]] == 'x')
                        printf("0");
                    else if (plansza[statekB.y[i] + a][statekB.x[i]] == '@' || plansza[statekB.y[i] + a][statekB.x[i]] == '%'
                        || plansza[statekB.y[i] + a][statekB.x[i]] == '!' || plansza[statekB.y[i] + a][statekB.x[i]] == '+')
                        printf("1");
                }
            }
            if (statekB.kierunek[i] == 'E') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekB.y[i]][statekB.x[i] - a] == 'x')
                        printf("0");
                    else if (plansza[statekB.y[i]][statekB.x[i] - a] == '@' || plansza[statekB.y[i]][statekB.x[i] - a] == '%'
                        || plansza[statekB.y[i]][statekB.x[i] - a] == '!' || plansza[statekB.y[i]][statekB.x[i] - a] == '+')
                        printf("1");
                }
            }
            if (statekB.kierunek[i] == 'W') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekB.y[i]][statekB.x[i] + a] == 'x')
                        printf("0");
                    else if (plansza[statekB.y[i]][statekB.x[i] + a] == '@' || plansza[statekB.y[i]][statekB.x[i] + a] == '%'
                        || plansza[statekB.y[i]][statekB.x[i] + a] == '!' || plansza[statekB.y[i]][statekB.x[i] + a] == '+')
                        printf("1");
                }
            }
            if (statekB.kierunek[i] == 'S') {
                for (int a = 0; a < typ; a++) {
                    if (plansza[statekB.y[i] - a][statekB.x[i]] == 'x')
                        printf("0");
                    else if (plansza[statekB.y[i] - a][statekB.x[i]] == '@' || plansza[statekB.y[i] - a][statekB.x[i]] == '%'
                        || plansza[statekB.y[i] - a][statekB.x[i]] == '!' || plansza[statekB.y[i] - a][statekB.x[i]] == '+')
                        printf("1");
                }
            }
            printf("\n");

        }
    }

    printf("[state]\n");
}