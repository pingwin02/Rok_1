#include <iostream>
#include "print.h"
#include "wazne.h"


void wydrukuj(int* width, int* height, char** plansza, int opcja, char kto) {

    switch (opcja) {
    case 0: { //gdy PRINT 0
        for (int i = 0; i < *height; i++) {
            for (int j = 0; j < *width; j++) {
                if (plansza[i][j] == '!' || plansza[i][j] == '@' || plansza[i][j] == '%')
                    printf("+");
                else printf("%c", plansza[i][j]);
            }
            printf("\n");
        }
        printf("PARTS REMAINING:: A : %d B : %d\n", statekA.ile_czesci, statekB.ile_czesci);
        break;
    }
    case 1: { //gdy PRINT 1
        if (*width > 10) {
            printf("  ");
            for (int i = 0; i < *width; i++) {
                printf("%d", i / 10);
            }
            printf("\n");
        }
        for (int i = -1; i < *height; i++) {
            for (int j = -1; j < *width; j++) {
                if (i == -1 && j == -1) printf("  ");
                else if (i == -1) {
                    printf("%d", j % 10);
                }
                else if (j == -1 && i < 10) printf("0%d", i);
                else if (j == -1 && i >= 10) printf("%d", i);
                else printf("%c", plansza[i][j]);
            }
            printf("\n");
        }
        printf("PARTS REMAINING:: A : %d B : %d\n", statekA.ile_czesci, statekB.ile_czesci);
        break;
    }
    case 10: { //gdy PRINT 0 w player
        for (int i = 0; i < *height; i++) {
            for (int j = 0; j < *width; j++) {
                if (mgla_wojny(kto, i, j) && (plansza[i][j] == '!' || plansza[i][j] == '@' || plansza[i][j] == '%'))
                    printf("+");
                else if (mgla_wojny(kto, i, j) || plansza[i][j] == '#')
                    printf("%c", plansza[i][j]);
                else
                    printf("?");
            }
            printf("\n");
        }
        break;
    }
    case 11: { //gdy PRINT 1 w player
        if (*width > 10) {
            printf("  ");
            for (int i = 0; i < *width; i++) {
                printf("%d", i / 10);
            }
            printf("\n");
        }
        for (int i = -1; i < *height; i++) {
            for (int j = -1; j < *width; j++) {
                if (i == -1 && j == -1) printf("  ");
                else if (i == -1) {
                    printf("%d", j % 10);
                }
                else if (j == -1 && i < 10) printf("0%d", i);
                else if (j == -1 && i >= 10) printf("%d", i);
                else if (mgla_wojny(kto, i, j) || plansza[i][j] == '#')
                    printf("%c", plansza[i][j]);
                else
                    printf("?");
            }
            printf("\n");
        }
        break;
    }
           //gdy opcja PRINT X bedzie nieprawidlowa
    default: {
        printf("INVALID OPERATION \"PRINT %d\": PRINT 0 OR PRINT 1 EXPECTED", opcja);
        exit(0);
    }
    }
}

bool mgla_wojny(char kto, int y, int x) { //funkcja oblicza mgle wojny dla PRINT w [player]

    int flaga = 0;
    int typ = 0;
    //dla statkow
    for (int i = 0; i < 40; i++) {
        if (i < 10) typ = DLUGOSC_CAR;
        else if (i < 20) typ = DLUGOSC_BAT;
        else if (i < 30) typ = DLUGOSC_CRU;
        else typ = DLUGOSC_DES;

        if (kto == 'A') {
            if (statekA.id[i] != 0) { //statek istnieje
                //gdy statek ma zniszczony radar, musi widziec rowniez siebie
                if (statekA.radar[i] == 1) {
                    if (statekA.kierunek[i] == 'N') {
                        for (int j = 0; j < typ; j++) {
                            if (y == statekA.y[i] + j && x == statekA.x[i]) flaga = 1;
                        }
                    }
                    if (statekA.kierunek[i] == 'E') {
                        for (int j = 0; j < typ; j++) {
                            if (x == statekA.x[i] - j && y == statekA.y[i]) flaga = 1;
                        }
                    }
                    if (statekA.kierunek[i] == 'W') {
                        for (int j = 0; j < typ; j++) {
                            if (x == statekA.x[i] + j && y == statekA.y[i]) flaga = 1;
                        }
                    }
                    if (statekA.kierunek[i] == 'S') {
                        for (int j = 0; j < typ; j++) {
                            if (y == statekA.y[i] - j && x == statekA.x[i]) flaga = 1;
                        }
                    }
                    typ = 1;
                }//wzor na zasieg
                if ((x - statekA.x[i]) * (x - statekA.x[i]) + (y - statekA.y[i]) * (y - statekA.y[i]) <= (typ * typ))
                    flaga = 1;
            }

        }
        if (kto == 'B') {
            if (statekB.id[i] != 0) {
                if (statekB.radar[i] == 1) {
                    if (statekB.kierunek[i] == 'N') {
                        for (int j = 0; j < typ; j++) {
                            if (y == statekB.y[i] + j && x == statekB.x[i]) flaga = 1;
                        }
                    }
                    if (statekB.kierunek[i] == 'E') {
                        for (int j = 0; j < typ; j++) {
                            if (x == statekB.x[i] - j && y == statekB.y[i]) flaga = 1;
                        }
                    }
                    if (statekB.kierunek[i] == 'W') {
                        for (int j = 0; j < typ; j++) {
                            if (x == statekB.x[i] + j && y == statekB.y[i]) flaga = 1;
                        }
                    }
                    if (statekB.kierunek[i] == 'S') {
                        for (int j = 0; j < typ; j++) {
                            if (y == statekB.y[i] - j && x == statekB.x[i]) flaga = 1;
                        }
                    }
                    typ = 1;
                }
                if ((x - statekB.x[i]) * (x - statekB.x[i]) + (y - statekB.y[i]) * (y - statekB.y[i]) <= (typ * typ))
                    flaga = 1;
            }

        }
    }
    //dla spy planow
    for (int i = 0; i < 5; i++) {
        typ = 2;//zasieg plane to zawsze 3x3

        if (kto == 'A') {
            if (statekA.spyID[i] != 0) {
                if ((x - statekA.spyX[i]) * (x - statekA.spyX[i]) + (y - statekA.spyY[i]) * (y - statekA.spyY[i]) < (typ * typ))
                    flaga = 1;
            }

        }
        if (kto == 'B') {
            if (statekB.spyID[i] != 0) {
                if ((x - statekB.spyX[i]) * (x - statekB.spyX[i]) + (y - statekB.spyY[i]) * (y - statekB.spyY[i]) < (typ * typ))
                    flaga = 1;
            }

        }
    }
    return flaga;
}