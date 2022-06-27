#pragma warning(disable:6031)
#pragma warning(disable:6386)
#pragma warning(disable:6385)
#ifndef wazne_h

#define wazne_h

#define MAX_DLUGOSC_KOMENDY 50

//domyslny rozmiar planszy
#define WYS_PLANSZY 21
#define SZER_PLANSZY 10

//definicja dlugosci statkow od klasy
#define DLUGOSC_CAR 5
#define DLUGOSC_BAT 4
#define DLUGOSC_CRU 3
#define DLUGOSC_DES 2

//max ilosc strzalow od danej klasy dla extended_ships
#define MAX_STRZAL_CAR 5
#define MAX_STRZAL_BAT 4
#define MAX_STRZAL_CRU 3
#define MAX_STRZAL_DES 2

//definicja zasiegu nieskonczonego
#define INF_ZASIEG 1000

//definicja max ilosci statkow jednej klasy
#define MAX_FLEET_SIZE 10

//max ilosc ruchu od danej klasy dla extended_ships
#define MAX_MOVE_CAR 2
#define MAX_MOVE_OTHER 3

int czykomenda(char* komenda, const char* komenda_oczekiwana);
int czywszystkiestatki();
char** wstawianie(int* width, int* height, char** plansza, char* komenda, char znak, int czywszystkiestatki, char kto, int* extended_ships);
void zmien_stan(char kto);
int sprawdzaj_stan();
char** stworztablice(int height, int width);
char** stworznowatablice(int height, int width);
int** stan_planszy(int height, int width, char** plansza);
void czujnik_rafa_statek(char* komenda, char** plansza, int typ, char kierunek, int x, int y, int id, char* klasa, int* width, int* height, char kto, int mode, char* damage, char droga);
void mojswap(char& tab1, char& tab2, int id, char* klasa, char droga);
void przypisaniebaza(int y, int x, char direction, char* klasa, int idSHIP, char kto);
int czyzaczeto();

struct statek_t {
    int y[4* MAX_FLEET_SIZE]; //0-9 CAR 10-19 BAT 20-29 CRU 30-39 DES
    int x[4* MAX_FLEET_SIZE];
    //lokalizacja silnika
    int silnikY[4* MAX_FLEET_SIZE];
    int silnikX[4* MAX_FLEET_SIZE];
    //lokalizacja dziala
    int dzialoY[4* MAX_FLEET_SIZE];
    int dzialoX[4* MAX_FLEET_SIZE];

    char kierunek[4* MAX_FLEET_SIZE];

    int ile_czesci = 0;
    int id[4* MAX_FLEET_SIZE] = { 0 };
    // ilosc statkow na mapie {jak duzo,ile jest} {CAR,BAT,CRU,DES}
    int fleet[4][2] = { {1, 0},{2, 0},{3, 0},{4, 0} };
    int radar[4* MAX_FLEET_SIZE] = { 0 };//radar sprawny 0, zniszczony 1
    int silnik[4* MAX_FLEET_SIZE] = { 0 };//silnik sprawny 0, zniszczony 1
    int dzialo[4* MAX_FLEET_SIZE] = { 0 };//dzialo sprawny 0, zniszczony 1

    //limit strzalow
    int limstrzal[4][2] = { {MAX_STRZAL_CAR, 0},{MAX_STRZAL_BAT, 0},{MAX_STRZAL_CRU, 0},{MAX_STRZAL_DES, 0} };

    //samolot szpieg
    int spyX[MAX_STRZAL_CAR];
    int spyY[MAX_STRZAL_CAR];
    int spyID[MAX_STRZAL_CAR] = { 0 };
};

extern struct statek_t statekA;
extern struct statek_t statekB;

#endif
