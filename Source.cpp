#include <iostream>
#include <stdlib.h>
#include <windows.h>

#include "drukowanie.h"
#include "zasady.h"

#define HEIGHT 23
#define WIDTH 70

using namespace std;


int main() {
    char plansza[3 * HEIGHT][3 * WIDTH]; //deklaracje tablic
    int stan[3 * HEIGHT][3 * WIDTH];
    for (int i = 0; i < 3 * HEIGHT; i++) { //wykropkowanie tablicy plansza
        for (int j = 0; j < 3 * WIDTH; j++)
            plansza[i][j] = ' ';
    }
    for (int i = 0; i < 3 * HEIGHT; i++) { //wyzerowanie tablicy stan
        for (int j = 0; j < 3 * WIDTH; j++)
            stan[i][j] = 0;
    }
    //przykladowe komorki startowe

    //dakota
    
     /* plansza [32][85] = 'o';
      plansza [35][85] = 'o';
      plansza [31][86] = 'o';
      plansza [31][87] = 'o';
      plansza [35][87] = 'o';
      plansza [31][88] = 'o';
      plansza [32][88] = 'o';
      plansza [33][88] = 'o';
      plansza [34][88] = 'o';
    */
    //samolot
    /*
      plansza [33][80]='o';
      plansza [33][81]='o';
      plansza [33][82]='o';
      plansza [34][80]='o';
      plansza [35][81]='o';
    */
    //die hard
  /*
    plansza [29][86]='o';
    plansza [30][80]='o';
    plansza [30][81]='o';
    plansza [31][81]='o';
    plansza [31][85]='o';
    plansza [31][86]='o';
    plansza [31][87]='o';
  */
  //niesmiertelny
/*
  plansza[29][80] = 'o';
  plansza[29][81] = 'o';
  plansza[29][82] = 'o';
  plansza[29][84] = 'o';
  plansza[30][80] = 'o';
  plansza[31][83] = 'o';
  plansza[31][84] = 'o';
  plansza[32][81] = 'o';
  plansza[32][82] = 'o';
  plansza[32][84] = 'o';
  plansza[33][80] = 'o';
  plansza[33][82] = 'o';
  plansza[33][84] = 'o';
*/
//single line
    
    plansza[32][74] = 'o';
    plansza[32][75] = 'o';
    plansza[32][76] = 'o';
    plansza[32][77] = 'o';
    plansza[32][78] = 'o';
    plansza[32][79] = 'o';
    plansza[32][80] = 'o';
    plansza[32][81] = 'o';
    plansza[32][83] = 'o';
    plansza[32][84] = 'o';
    plansza[32][85] = 'o';
    plansza[32][86] = 'o';
    plansza[32][87] = 'o';
    plansza[32][91] = 'o';
    plansza[32][92] = 'o';
    plansza[32][93] = 'o';
    plansza[32][100] = 'o';
    plansza[32][101] = 'o';
    plansza[32][102] = 'o';
    plansza[32][103] = 'o';
    plansza[32][104] = 'o';
    plansza[32][105] = 'o';
    plansza[32][106] = 'o';
    plansza[32][108] = 'o';
    plansza[32][109] = 'o';
    plansza[32][110] = 'o';
    plansza[32][111] = 'o';
    plansza[32][112] = 'o';
    
    for (int i = 0; i < 5000; i++) { //iteracje zycia
        cout << i << endl;
        int* p = &i;
        drukuj(plansza);
        //system("pause");
        Sleep(80);
        system("CLS");
        zycie(plansza, stan);
        int flaga = 0;
        for (int i = 0; i < 3 * HEIGHT; i++) { //sprawdzanie zycia
            for (int j = 0; j < 3 * WIDTH; j++)
                if (stan[i][j] == 1) flaga++;
        }
        if (flaga == 0) {
            drukuj(plansza);
            cout << "Zycie skonczylo sie po " << *p + 1 << " iteracjach. Koncze program" << endl;
            return 404;
        }
    }
    return 0;
}
