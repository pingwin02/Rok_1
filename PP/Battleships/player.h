#ifndef player_h

#define player_h


void flota(int* width, int* height, char** plansza, char* komenda, char kto, int init_positions[][2],int mode, int* extended_ships);
void umieszczanie(int* width, int* height, char** plansza, int y, int x, int typ, char kierunek, int id, char* klasa, char* komenda, char kto, int init_positions[][2],int mode, int* extended_ships);
void player(int* width, int* height, char* komenda, char** plansza, int ifjustclosedX, char kto, const char* player0, const char* player1, int init_positions[][2], int ruch[][2], int* extended_ships);
void szpieg(char kto, int* height, int* width);

#endif
