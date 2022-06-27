#ifndef state_h

#define state_h

char** fstate(int* width, int* height, char* komenda, char** plansza, int* ijcX, int init_positions[][2], int* extended_ships);
void fnext_player(int* ifjustclosedX);
void setfleet();
void finit_position(int init_positions[][2], int* width, int* height);
char** zmienrozmiar(int* width, int* height, char** plansza, int init_positions[][2]);
void fship(char* komenda, char** plansza, int* width, int* height, int init_positions[][2], int* extended_ships);
void fsave(int* width, int* height, int* ijcX, int init_positions[][2], int* extended_ships, char** plansza);

#endif
