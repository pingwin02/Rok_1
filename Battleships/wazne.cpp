#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "wazne.h"

struct statek_t statekA;
struct statek_t statekB;

int czykomenda(char* komenda, const char* komenda_oczekiwana) { //funkcja porownuje komendy

    while (strcmp(komenda, komenda_oczekiwana) == 0)
        return 1;

    return 0;
}
int czywszystkiestatki() { //funkcja sprawdza czy wszystkie statki sa juz na mapie i czy mozna juz strzelac itd
    int czujka = 0;
    for (int i = 0; i < 4; i++)
    {
        if (statekA.fleet[i][0] != statekA.fleet[i][1])czujka++;
        if (statekB.fleet[i][0] != statekB.fleet[i][1])czujka++;
    }
    if (czujka != 0) return 404; //nie ma wszystkich statkow
    else return 0; //sa wszystkie
}
int czyzaczeto() { //funkcja sprawdza czy zaczeto grac, info dla komendy BOARD_SIZE

    if (statekA.ile_czesci != 0 || statekB.ile_czesci != 0) return 1; //zaczeto
    else return 0; //nie zaczeto
}
char** wstawianie(int* width, int* height, char** plansza, char* komenda, char znak, int czywszystkiestatki, char kto, int* extended_ships) {

    int y = 0;
    int x = 0;

    if (*extended_ships == 1) { //jesli wlaczony tryb extended_ships
        int id, dodaj = 0;
        int zasieg = 0;
        char klasa[4]{};
        std::cin >> id;
        scanf("%3s", klasa);
        std::cin >> y >> x;

        //do poruszania sie po bazie danych oraz walidacji
        if (czykomenda(klasa, "CAR")) {
            dodaj = 0;
            zasieg = INF_ZASIEG; //dla carrier zasieg nieskonczony
        }
        else if (czykomenda(klasa, "BAT")) { 
            dodaj = 10;
            zasieg = DLUGOSC_BAT + 1;
        }
        else if (czykomenda(klasa, "CRU")) { 
            dodaj = 20;
            zasieg = DLUGOSC_CRU + 1;
        }
        else if (czykomenda(klasa, "DES")) { 
            dodaj = 30;
            zasieg = DLUGOSC_DES + 1;
        }

        //jesli statek o podanym id i klasie nie istnieje
        if ((kto == 'A' && statekA.id[id + dodaj] == 0) || (kto == 'B' && statekB.id[id + dodaj] == 0))
        {
            printf("INVALID OPERATION \"%s %d %s %d %d\": SHIP NOT FOUND", komenda, id, klasa, y, x);
            exit(0);
        }

        //jesli dzialo zniszczone statek nie moze strzelac
        if ((kto == 'A' && statekA.dzialo[id + dodaj] == 1) || (kto == 'B' && statekB.dzialo[id + dodaj] == 1))
        {
            printf("INVALID OPERATION \"%s %d %s %d %d\": SHIP CANNOT SHOOT", komenda, id, klasa, y, x);
            exit(0);
        }
        //walidacja zasiegu strzalu

        if (kto == 'A') {
            if (statekA.id[id+dodaj] != 0) { //jesli statek istnieje
                if ((x - statekA.x[id+dodaj]) * (x - statekA.x[id+dodaj]) + (y - statekA.y[id+dodaj]) * (y - statekA.y[id+dodaj]) > (zasieg * zasieg)) {
                    printf("INVALID OPERATION \"%s %d %s %d %d\": SHOOTING TOO FAR", komenda, id, klasa, y, x);
                    exit(0);
                }

            }

        }
        if (kto == 'B') {
            if (statekB.id[id+dodaj] != 0) {
                if ((x - statekB.x[id+dodaj]) * (x - statekB.x[id+dodaj]) + (y - statekB.y[id+dodaj]) * (y - statekB.y[id+dodaj]) > (zasieg * zasieg)) {
                    printf("INVALID OPERATION \"%s %d %s %d %d\": SHOOTING TOO FAR", komenda, id, klasa, y, x);
                    exit(0);
                }
            }
        }

        dodaj = dodaj / 10; //CAR 0 BAT 1 CRU 2 DES 3
        if (kto == 'A') { //liczenie i walidacja ilosci strzalow
            statekA.limstrzal[0 + dodaj][1]++;
        }
        else if (kto == 'B') {
            statekB.limstrzal[0 + dodaj][1]++;
        }
        //walidacja ilosci strzalow
        if ((kto == 'A' && (statekA.limstrzal[0 + dodaj][1] > statekA.limstrzal[0 + dodaj][0])) || ((kto == 'B' && (statekB.limstrzal[0 + dodaj][1] > statekB.limstrzal[0 + dodaj][0])))) {
            printf("INVALID OPERATION \"%s %d %s %d %d\": TOO MANY SHOOTS", komenda, id, klasa, y, x);
            exit(0);
        }

        if (plansza[y][x] == '%') { //jesli strzal trafi w silnik ustaw statkowi na odpowiednich wspolrzednych silnik jako zniszczony
            for (int i = 0; i < 40; i++) {
                if (y == statekA.silnikY[i] && x == statekA.silnikX[i]) statekA.silnik[i] = 1;
                if (y == statekB.silnikY[i] && x == statekB.silnikX[i]) statekB.silnik[i] = 1;
            }
        }
        if (plansza[y][x] == '!') { //jesli strzal trafi w dzialo ustaw statkowi na odpowiednich wspolrzednych dzialo jako zniszczone
            for (int i = 0; i < 30; i++) {
                if (y == statekA.dzialoY[i] && x == statekA.dzialoX[i]) statekA.dzialo[i] = 1;
                if (y == statekB.dzialoY[i] && x == statekB.dzialoX[i]) statekB.dzialo[i] = 1;
            }
        }
        if (plansza[y][x] == '%') { //jesli strzal trafi w dzialo dla destroyera
            for (int i = 30; i < 40; i++) {
                if (y == statekA.dzialoY[i] && x == statekA.dzialoX[i]) statekA.dzialo[i] = 1;
                if (y == statekB.dzialoY[i] && x == statekB.dzialoX[i]) statekB.dzialo[i] = 1;
            }
        }
    }

    else std::cin >> y >> x; //wykonaj gdy extended_ships jest wylaczone

    if (y >= *height || x >= *width || y < 0 || x < 0) { //reef lub shoot poza zakres mapy
        if (znak == '#') {//gdy reef
            printf("INVALID OPERATION \"%s %d %d\": REEF IS NOT PLACED ON BOARD", komenda, y, x);
            exit(0);
        }
        else {
            printf("INVALID OPERATION \"%s %d %d\": FIELD DOES NOT EXIST", komenda, y, x);
            exit(0);
        }
    }
    else if (czywszystkiestatki == 404) { //jesli nie ma wszystkich statkow na mapie
        printf("INVALID OPERATION \"%s %d %d\": NOT ALL SHIPS PLACED", komenda, y, x);
        exit(0);
    }
    if ((plansza[y][x] == ' '|| plansza[y][x] == '#') && znak == 'x') return plansza; //jesli strzal w wode lub rafe, nic nie rob
    //gdy trafisz w statek dokonaj zmiany w bazie danych statekX.ile_czesci
    if (znak!='#'&&(plansza[y][x] == '+' || plansza[y][x] == '!' || plansza[y][x] == '@' || plansza[y][x] == '%')) zmien_stan(kto);

    if (plansza[y][x] == '@') { //jesli strzal trafi w radar ustaw statkowi na odpowiednich wspolrzednych radar jako zniszczony
        for (int i = 0; i < 40; i++) {
            if (y == statekA.y[i] && x == statekA.x[i]) statekA.radar[i] = 1;
            if (y == statekB.y[i] && x == statekB.x[i]) statekB.radar[i] = 1;
        }
    }
    plansza[y][x] = znak; //wpisz znak do planszy
    return plansza;
}
void mojswap(char& tab1, char& tab2, int id, char* klasa, char droga) { //funkcja do zamiany wartosci w tablicy
    char temp;
    temp = tab1;
    tab1 = tab2;
    tab2 = temp;
    if (tab1 == '#' || tab2 == '#') { //walidator rafy przy poruszaniu
        printf("INVALID OPERATION \"MOVE %d %s %c\": PLACING SHIP ON REEF", id, klasa, droga);
        exit(0);
    }
}


void zmien_stan(char kto) { //funkcja zmienia o 1 ilosc aktywnych czesci gracza X jesli wykryto trafienie gracza Y

    if (kto == 'A')statekB.ile_czesci--;
    else if (kto == 'B')statekA.ile_czesci--;
}

int sprawdzaj_stan() {

    if (statekA.ile_czesci == 0) return 2; //jesli gracz a stracil statki, oglos wygrana gracza b
    else if (statekB.ile_czesci == 0) return 1; //jesli gracz b stracil statki, oglos wygrana gracza a
    else return 0; //w innym wypadku kontynuuuj gre
}
char** stworztablice(int height, int width) { //funkcja tworzy nowa plansze
    char** plansza = new char* [height];
    for (int i = 0; i < height; i++) {
        plansza[i] = new char[height];
        for (int j = 0; j < width; j++) {
            plansza[i][j] = ' ';
        }
    }
    return plansza;
}
char** stworznowatablice(int height, int width) { //funkcja tworzy nowa plansze po zmianie rozmiaru
    char** plansza = new char* [height];
    for (int i = 0; i < height; i++) {
        plansza[i] = new char[height];
        for (int j = 0; j < width; j++) {
            plansza[i][j] = ' ';
        }
    }
    return plansza;
}

int** stan_planszy(int height, int width, char** plansza) { //tworzy tablice zer i jedynek ktore odpowiadaja polozeniom statkow na mapie 1-jest statek 0-nie ma

    int** plansza_inna = new int* [height];
    for (int i = 0; i < height; i++) {
        plansza_inna[i] = new int[height];
        for (int j = 0; j < width; j++) {
            plansza_inna[i][j] = 0; //wyzerowanie tablicy
        }
    }


    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (plansza[i][j] == '+' || plansza[i][j] == '!' || plansza[i][j] == '@' || plansza[i][j] == '%' || plansza[i][j] == 'x') //jesli napotkasz + ! @ x lub % wstaw 1 w odpowiednie miejsce
                plansza_inna[i][j] = 1;
        }
    }

    return plansza_inna;
}
//mode 0 - komenda PLACE_SHIP, mode 1 - komenda SHIP, mode 2 - komenda MOVE
void czujnik_rafa_statek(char* komenda, char** plansza, int typ, char kierunek, int x, int y, int id, char* klasa, int* width, int* height, char kto, int mode, char* damage, char droga) {

    int** plansza_inna = stan_planszy(*height, *width, plansza);//wygenerowanie planszy 0 i 1

    switch (kierunek) {
    case 'S': {
        for (int i = 0; i < typ; i++) {
            if (plansza[y - i][x] == '#') {//gdy napotkasz rafe
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP ON REEF");
                exit(0);
            }
            //gdy napotkasz statek
            else if ((x > 0 && plansza_inna[y - i][x - 1] == 1) || (x < *width - 1 && plansza_inna[y - i][x + 1] == 1) || (y < *height - 1 && plansza_inna[y + 1][x] == 1) || plansza_inna[y - typ][x] == 1) {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP TOO CLOSE TO OTHER SHIP");
                exit(0);
            }
        }
        break;
    }
    case 'W': {
        for (int i = 0; i < typ; i++) {
            if (plansza[y][x + i] == '#') {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP ON REEF");
                exit(0);
            }
            else if ((y < *height - 1 && plansza_inna[y + 1][x + i] == 1) || (y > 0 && plansza_inna[y - 1][x + i] == 1) || (x > 0 && plansza_inna[y][x - 1] == 1) || plansza_inna[y][x + typ] == 1) {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP TOO CLOSE TO OTHER SHIP");
                exit(0);
            }
        }
        break;
    }
    case 'N': {
        for (int i = 0; i < typ; i++) {
            if (plansza[y + i][x] == '#') {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP ON REEF");
                exit(0);
            }
            else if ((x > 0 && plansza_inna[y + i][x - 1] == 1) || (x < *width - 1 && plansza_inna[y + i][x + 1] == 1) || (y > 0 && plansza_inna[y - 1][x] == 1) || plansza_inna[y + typ][x] == 1) {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP TOO CLOSE TO OTHER SHIP");
                exit(0);
            }
        }
        break;
    }
    case 'E': {
        for (int i = 0; i < typ; i++) {
            if (plansza[y][x + i] == '#') {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP ON REEF");
                exit(0);
            }
            else  if ((y < *height - 1 && plansza_inna[y + 1][x - i] == 1) || (y > 0 && plansza_inna[y - 1][x - i] == 1) || (x < *width - 1 && plansza_inna[y][x + 1] == 1) || plansza_inna[y][x - typ] == 1) {
                printf("INVALID OPERATION \"%s ", komenda);
                if (mode == 1)printf("%c ", kto);
                if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
                printf("%d %s", id, klasa);
                if (mode == 2)printf(" %c", droga);
                if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
                printf("\": PLACING SHIP TOO CLOSE TO OTHER SHIP");
                exit(0);
            }
        }
        break;
    }
    default: { //gdy kierunek jest nie poprawny
        printf("INVALID OPERATION \"%s ", komenda);
        if (mode == 1)printf("%c ", kto);
        if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
        printf("%d %s", id, klasa);
        if (mode == 2)printf("%c ", droga);
        if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
        printf("\": OTHER ERROR WHILE PLACING SHIP");
        exit(0);
    }
    }

    for (int i = 0; i < *height; i++) //zwolnij pamiec, usun plansze 0 i 1
    {
        delete[] plansza_inna[i];
    }
    delete[] plansza_inna;
}

void przypisaniebaza(int y, int x, char direction, char* klasa, int idSHIP, char kto) { //funckja przypisuje do bazy danych info dot. statkow


    switch (kto) {

    case 'A': {
        if (czykomenda(klasa, "CAR")) {
            statekA.y[idSHIP] = y;
            statekA.x[idSHIP] = x;
            statekA.kierunek[idSHIP] = direction;
            statekA.id[idSHIP] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "BAT")) {
            statekA.y[idSHIP + 10] = y;
            statekA.x[idSHIP + 10] = x;
            statekA.kierunek[idSHIP + 10] = direction;
            statekA.id[idSHIP + 10] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "CRU")) {
            statekA.y[idSHIP + 20] = y;
            statekA.x[idSHIP + 20] = x;
            statekA.kierunek[idSHIP + 20] = direction;
            statekA.id[idSHIP + 20] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "DES")) {
            statekA.y[idSHIP + 30] = y;
            statekA.x[idSHIP + 30] = x;
            statekA.kierunek[idSHIP + 30] = direction;
            statekA.id[idSHIP + 30] = idSHIP + 1;
        }
        break;
    }
    case 'B': {
        if (czykomenda(klasa, "CAR")) {
            statekB.y[idSHIP] = y;
            statekB.x[idSHIP] = x;
            statekB.kierunek[idSHIP] = direction;
            statekB.id[idSHIP] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "BAT")) {
            statekB.y[idSHIP + 10] = y;
            statekB.x[idSHIP + 10] = x;
            statekB.kierunek[idSHIP + 10] = direction;
            statekB.id[idSHIP + 10] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "CRU")) {
            statekB.y[idSHIP + 20] = y;
            statekB.x[idSHIP + 20] = x;
            statekB.kierunek[idSHIP + 20] = direction;
            statekB.id[idSHIP + 20] = idSHIP + 1;
        }
        else if (czykomenda(klasa, "DES")) {
            statekB.y[idSHIP + 30] = y;
            statekB.x[idSHIP + 30] = x;
            statekB.kierunek[idSHIP + 30] = direction;
            statekB.id[idSHIP + 30] = idSHIP + 1;
        }
        break;
    }
    default: exit(0);
    }
}
