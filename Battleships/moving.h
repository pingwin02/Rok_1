#ifndef moving_h

#define moving_h

void fmove(char kto, char** plansza, int* width, int* height, int ruch[][2], int* extended_ships);
void movingships(char kto, int id, int dodaj, int typ, char* klasa, char droga, char** plansza, int* width, int* height);

#endif
