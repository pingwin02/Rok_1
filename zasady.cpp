#include "zasady.h"

//MAX SASIADOW 8

#define ILE_SASIADOW_BY_ZYC 3 //liczba sasiadow przy ktorej komorka ozywa

#define ILE_SASIADOW_BY_NIE_UMRZEC_1 3
#define ILE_SASIADOW_BY_NIE_UMRZEC_2 2 //liczba sasiadow przy ktorej komorka wciaz zyje


void zycie(char plansza[][3 * WIDTH], int stan[][3 * WIDTH]) {
    int sasiad;
    for (int i = 0; i < 3 * HEIGHT; i++) {
        for (int j = 0; j < 3 * WIDTH; j++) {
            if (plansza[i][j] == ' ') { //jesli komorka nie zyje
                sasiad = 0;
                if (plansza[i + 1][j] == 'o') sasiad++;
                if (plansza[i - 1][j] == 'o') sasiad++;
                if (plansza[i][j + 1] == 'o') sasiad++;
                if (plansza[i][j - 1] == 'o') sasiad++;
                if (plansza[i - 1][j - 1] == 'o') sasiad++;
                if (plansza[i + 1][j + 1] == 'o') sasiad++;
                if (plansza[i + 1][j - 1] == 'o') sasiad++;
                if (plansza[i - 1][j + 1] == 'o') sasiad++;
                if (sasiad == ILE_SASIADOW_BY_ZYC) stan[i][j] = 1; //jesli ma 3 sasiadow, ozyw ja
                else stan[i][j] = 0; //w przeciwnym wypadku zapisz jej stan jako 0
            }
            else if (plansza[i][j] == 'o') { //jesli komorka zyje
                sasiad = 0;
                if (plansza[i + 1][j] == 'o') sasiad++;
                if (plansza[i - 1][j] == 'o') sasiad++;
                if (plansza[i][j + 1] == 'o') sasiad++;
                if (plansza[i][j - 1] == 'o') sasiad++;
                if (plansza[i - 1][j - 1] == 'o') sasiad++;
                if (plansza[i + 1][j + 1] == 'o') sasiad++;
                if (plansza[i + 1][j - 1] == 'o') sasiad++;
                if (plansza[i - 1][j + 1] == 'o') sasiad++;
                if (!(sasiad == ILE_SASIADOW_BY_NIE_UMRZEC_1 || sasiad == ILE_SASIADOW_BY_NIE_UMRZEC_2)) stan[i][j] = 0; //jesli ma 0, 1, 4 i wiecej sasiadow, zabij ja
                else stan[i][j] = 1; //w przeciwnym wypadku zapisz jej stan jako 1
            }
        }
    }
    //przypisanie stanu do tablicy plansza
    for (int i = 0; i < 3 * HEIGHT; i++) {
        for (int j = 0; j < 3 * WIDTH; j++) {
            if (stan[i][j] == 0) plansza[i][j] = ' ';
            else if (stan[i][j] == 1) plansza[i][j] = 'o';
        }
    }

}
