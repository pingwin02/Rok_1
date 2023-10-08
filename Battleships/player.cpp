#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include "player.h"
#include "wazne.h"
#include "moving.h"
#include "print.h"


void player(int* width, int* height, char* komenda, char** plansza, int ifjustclosedX, char kto, const char* player0, const char* player1, int init_positions[][2], int ruch[][2], int* extended_ships) {
    const char place_ship[] = "PLACE_SHIP";
    const char shoot[] = "SHOOT";
    const char move[] = "MOVE";
    const char print[] = "PRINT";
    const char spy[] = "SPY";
    int shootA = 0; //1-gracz strzelal w tej rundzie 0-gracz nie strzelal
    int shootB = 0;
    do {
        if ((kto == 'A' && ifjustclosedX == 10) || (kto == 'B' && ifjustclosedX == 01)) { //walidacja kolejki
            printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED", komenda); exit(0);
        }

        scanf("%49s", komenda);

        if (czykomenda(komenda, place_ship)) { //komenda PLACE_SHIP
            flota(width, height, plansza, komenda, kto, init_positions, 0, extended_ships);
        }
        else if (czykomenda(komenda, shoot)) { //komenda SHOOT
            if (*extended_ships == 0) { //walidacja dla basic mode, jeden strzal na ruch
                if (shootA == 1 || shootB == 1) { printf("INVALID OPERATION \"%s\": YOU CAN SHOOT ONLY ONCE PER ROUND", komenda); exit(0); }
                if (kto == 'A') shootA = 1;
                else if (kto == 'B') shootB = 1;
            }
            wstawianie(width, height, plansza, komenda, 'x', czywszystkiestatki(), kto, extended_ships);
        }
        else if (czykomenda(komenda, move)) { //komenda MOVE
            fmove(kto, plansza, width, height, ruch, extended_ships);
        }
        else if (czykomenda(komenda, print)) { //komenda PRINT
            int x;
            std::cin >> x;
            x += 10;//dla case w funkcji wydrukuj gdy 0 to 10 gdy 1 to 11
            wydrukuj(width, height, plansza, x, kto);
        }
        else if (czykomenda(komenda, spy)) { //komenda SPY
            szpieg(kto, height, width);
        }
        else if (czykomenda(komenda, player1)) { //jesli komenda to [playerY] gdy otwarty jest [playerX] wydrukuj blad
            printf("INVALID OPERATION \"%s\": THE OTHER PLAYER EXPECTED", komenda);
            exit(0);
        }
        else if (czykomenda(komenda, player0) == 0) { //gdy bledna komenda
            printf("INVALID OPERATION \"%s\": EXPECTED COMMANDS: SHOOT, PLACE_SHIP, MOVE", komenda);
            exit(0);
        }
    } while (czykomenda(komenda, player0) == 0);

    for (int i = 0; i < 4; i++) //wyzerowanie uzyc komendy MOVE
        ruch[i][1] = 0;
    for (int i = 0; i < 4; i++) {//wyzerowanie uzyc komendy SPY
        statekA.limstrzal[i][1] = 0;
        statekB.limstrzal[i][1] = 0;
    }

}
//mode 0 - komenda PLACE_SHIP, mode 1 - komenda SHIP, mode 2 - komenda MOVE
void flota(int* width, int* height, char** plansza, char* komenda, char kto, int init_positions[][2], int mode, int* extended_ships) {
    int x, y, id;
    char klasa[4]{};
    char kierunek;
    const char car[] = "CAR"; //dlugosc 5
    const char bat[] = "BAT"; //dlugosc 4
    const char cru[] = "CRU"; //dlugosc 3
    const char des[] = "DES"; //dlugosc 2
    std::cin >> y >> x >> kierunek >> id;

    scanf("%3s", klasa);

    if (id > MAX_FLEET_SIZE || id < 0) { //walidacja id
        printf("INVALID OPERATION \"%s ", komenda);
        printf("%d %d %c %d %s\": INVALID ID", y, x, kierunek, id, klasa);
        exit(0);
    }

    if (y >= *height || x >= *width || y < 0 || x < 0) { //walidacja czy punkt znajduje sie na planszy
        printf("INVALID OPERATION \"%s ", komenda);
        printf("%d %d %c %d %s\": NOT IN STARTING POSITION", y, x, kierunek, id, klasa);
        exit(0);
    }
    //walidacja czy punkt znajduje sie w pozycjach poczatkowych graczy dla PLACE_SHIP
    else if ((mode == 0 && kto == 'A' && (x< init_positions[0][0] || x > init_positions[2][0] || y< init_positions[1][0] || y > init_positions[3][0])) ||
        (mode == 0 && kto == 'B' && (x< init_positions[0][1] || x > init_positions[2][1] || y< init_positions[1][1] || y > init_positions[3][1]))) {
        printf("INVALID OPERATION \"%s ", komenda);
        printf("%d %d %c %d %s\": NOT IN STARTING POSITION", y, x, kierunek, id, klasa);
        exit(0);
    }

    //klasa carrier
    if (czykomenda(klasa, car)) {
        //dodanie do bazy danych info o ilosci czesci statkow oraz ze statek zostal dodany
        if (kto == 'A') {
            statekA.ile_czesci += DLUGOSC_CAR;
            statekA.fleet[0][1]++;
        }
        else if (kto == 'B') {
            statekB.ile_czesci += DLUGOSC_CAR;
            statekB.fleet[0][1]++;
        }
        //walidacja czy statek o podanym id juz istnieje
        if ((kto == 'A' && statekA.id[id] == id + 1) || (kto == 'B' && statekB.id[id] == id + 1)) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": SHIP ALREADY PRESENT", y, x, kierunek, id, klasa);
            exit(0);
        }
        //walidacja czy wszystkie statki o tej klasie zostaly dodane
        if ((kto=='A'&& statekA.fleet[0][0] < statekA.fleet[0][1])|| (kto == 'B' && statekB.fleet[0][0] < statekB.fleet[0][1])) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET", y, x, kierunek, id, klasa);
            exit(0);
        }
        umieszczanie(width, height, plansza, y, x, DLUGOSC_CAR, kierunek, id, klasa, komenda, kto, init_positions, mode, extended_ships);
    }
    //klasa battleship
    else if (czykomenda(klasa, bat)) {
        //dodanie do bazy danych info o ilosci czesci statkow oraz ze statek zostal dodany
        if (kto == 'A') {
            statekA.ile_czesci += DLUGOSC_BAT;
            statekA.fleet[1][1]++;
        }
        else if (kto == 'B') {
            statekB.ile_czesci += DLUGOSC_BAT;
            statekB.fleet[1][1]++;
        }
        //walidacja czy statek o podanym id juz istnieje
        if ((kto == 'A' && statekA.id[id + 10] == id + 1) || (kto == 'B' && statekB.id[id + 10] == id + 1)) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": SHIP ALREADY PRESENT", y, x, kierunek, id, klasa);
            exit(0);
        }
        //walidacja czy wszystkie statki o tej klasie zostaly dodane
        if ((kto == 'A' && statekA.fleet[1][0] < statekA.fleet[1][1]) || (kto == 'B' && statekB.fleet[1][0] < statekB.fleet[1][1])) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET", y, x, kierunek, id, klasa);
            exit(0);
        }
        umieszczanie(width, height, plansza, y, x, DLUGOSC_BAT, kierunek, id, klasa, komenda, kto, init_positions, mode, extended_ships);
    }
    //klasa cruiser
    else if (czykomenda(klasa, cru)) {
        if (kto == 'A') {
            statekA.ile_czesci += DLUGOSC_CRU;
            statekA.fleet[2][1]++;
        }
        else if (kto == 'B') {
            statekB.ile_czesci += DLUGOSC_CRU;
            statekB.fleet[2][1]++;
        }
        if ((kto == 'A' && statekA.id[id + 20] == id + 1) || (kto == 'B' && statekB.id[id + 20] == id + 1)) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": SHIP ALREADY PRESENT", y, x, kierunek, id, klasa);
            exit(0);
        }
        if ((kto == 'A' && statekA.fleet[2][0] < statekA.fleet[2][1]) || (kto == 'B' && statekB.fleet[2][0] < statekB.fleet[2][1])) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET", y, x, kierunek, id, klasa);
            exit(0);
        }
        umieszczanie(width, height, plansza, y, x, DLUGOSC_CRU, kierunek, id, klasa, komenda, kto, init_positions, mode, extended_ships);
    }
    //klasa destroyer
    else if (czykomenda(klasa, des)) {
        if (kto == 'A') {
            statekA.ile_czesci += DLUGOSC_DES;
            statekA.fleet[3][1]++;
        }
        else if (kto == 'B') {
            statekB.ile_czesci += DLUGOSC_DES;
            statekB.fleet[3][1]++;
        }
        if ((kto == 'A' && statekA.id[id + 30] == id + 1) || (kto == 'B' && statekB.id[id + 30] == id + 1)) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": SHIP ALREADY PRESENT", y, x, kierunek, id, klasa);
            exit(0);
        }
        if ((kto == 'A' && statekA.fleet[3][0] < statekA.fleet[3][1]) || (kto == 'B' && statekB.fleet[3][0] < statekB.fleet[3][1])) {
            printf("INVALID OPERATION \"%s ", komenda);
            printf("%d %d %c %d %s\": ALL SHIPS OF THE CLASS ALREADY SET", y, x, kierunek, id, klasa);
            exit(0);
        }
        umieszczanie(width, height, plansza, y, x, DLUGOSC_DES, kierunek, id, klasa, komenda, kto, init_positions, mode, extended_ships);
    }
    //gdy podana klasa jest nieprawidlowa
    else {
        printf("INVALID OPERATION \"%s ", komenda);
        printf("%d %d %c %d %s\": CHOOSE FROM [CAR]RIER, [BAT]TLESHIP, [CRU]ISER, [DES]TROYER", y, x, kierunek, id, klasa);
        exit(0);
    }
    przypisaniebaza(y, x, kierunek, klasa, id, kto); //przypisanie do bazy statkow
}

void umieszczanie(int* width, int* height, char** plansza, int y, int x, int typ, char kierunek, int id, char* klasa, char* komenda, char kto, int init_positions[][2], int mode, int* extended_ships) {
    char damage[5] = { '1','1','1','1','1' };

    //do poruszania sie po bazie danych
    int dodaj = 0;
    if (czykomenda(klasa, "CAR")) dodaj = 0;
    else if (czykomenda(klasa, "BAT")) dodaj = 10;
    else if (czykomenda(klasa, "CRU")) dodaj = 20;
    else if (czykomenda(klasa, "DES")) dodaj = 30;

    //tryb komendy SHIP
    if (mode == 1) {
        for (int i = 0; i < typ; i++)
        {
            std::cin >> damage[i];
        }
        //jesli pierwsza cyfra w ship przy podawaniu obrazen jest 0, ustaw radar jako zniszczony
        if (damage[0] == '0') {
            if (kto == 'A')
                statekA.radar[id + dodaj] = 1;
            if (kto == 'B')
                statekB.radar[id + dodaj] = 1;
        }
        if (*extended_ships == 1) { //tylko gdy extended_ships jest wlaczone
            //jesli druga cyfra w ship przy podawaniu obrazen jest 0, ustaw dzialo jako zniszczone
            if (damage[1] == '0' == 0) {
                if (kto == 'A')
                    statekA.dzialo[id + dodaj] = 1;
                if (kto == 'B')
                    statekB.dzialo[id + dodaj] = 1;
            }
            //jesli ostatnia cyfra w ship przy podawaniu obrazen jest 0, ustaw silnik jako zniszczony
            if (damage[typ - 1] == '0') {
                if (kto == 'A')
                    statekA.silnik[id + dodaj] = 1;
                if (kto == 'B')
                    statekB.silnik[id + dodaj] = 1;
            }
        }

    }
    if (plansza[y][x] == '!' || plansza[y][x] == '@' || plansza[y][x] == '%' || plansza[y][x] == '+') { //walidacja czy statek nie jest kladzony na innym
        printf("INVALID OPERATION \"%s ", komenda);
        if (mode == 1)printf("%c ", kto);
        if (mode == 0 || mode == 1)printf("%d %d %c ", y, x, kierunek);
        printf("%d %s", id, klasa);
        if (mode == 1) { printf(" "); for (int j = 0; j < typ; j++)printf("%c", damage[j]); }
        printf("\": PLACING SHIP TOO CLOSE TO OTHER SHIP");
        exit(0);
    }

    //ustawanie statkow na mapie ze wzgledu na kierunek
    switch (kierunek) {
    case 'S': {

        if ((kto == 'A' && y - typ + 1 < init_positions[1][0] && mode == 0) || (kto == 'B' && y - typ + 1 < init_positions[1][1] && mode == 0)) {
            printf("INVALID OPERATION \"%s %d %d %c %d %s\": NOT IN STARTING POSITION", komenda, y, x, kierunek, id, klasa);
            exit(0);
        }
        for (int i = 0; i < typ; i++) {
            if (i == 0) plansza[y - i][x] = '@';
            else if (i == typ - 1) plansza[y - i][x] = '%';
            else if (i == 1) plansza[y - i][x] = '!';
            else  plansza[y - i][x] = '+';
            //przypisanie do bazy lokalizacji dziala i silnika
            if (i == typ - 1) {
                if (kto == 'A')
                {
                    statekA.silnikY[id + dodaj] = y - i;
                    statekA.silnikX[id + dodaj] = x;
                }
                if (kto == 'B')
                {
                    statekB.silnikY[id + dodaj] = y - i;
                    statekB.silnikX[id + dodaj] = x;
                }
            }
            if (i == 1) {
                if (kto == 'A')
                {
                    statekA.dzialoY[id + dodaj] = y - i;
                    statekA.dzialoX[id + dodaj] = x;
                }
                if (kto == 'B')
                {
                    statekB.dzialoY[id + dodaj] = y - i;
                    statekB.dzialoX[id + dodaj] = x;
                }

            }
        }
        //walidacja bliskosci statkow i rafy
        czujnik_rafa_statek(komenda, plansza, typ, kierunek, x, y, id, klasa, width, height, kto, mode, damage, 'X');
        //jesli tryb extended_ships sciagnij z inputu dane o obrazeniach
        if (mode == 1) {
            for (int i = 0; i < typ; i++)
            {
                if (damage[i] == '0') {
                    plansza[y - i][x] = 'x';
                    if (kto == 'A')zmien_stan('B');
                    else if (kto == 'B')zmien_stan('A');

                }
            }

        }
        break;
    }
    case 'W': {
        if ((kto == 'A' && x + typ - 1 > init_positions[2][0] && mode == 0) || (kto == 'B' && x + typ - 1 > init_positions[2][1] && mode == 0)) {
            printf("INVALID OPERATION \"%s %d %d %c %d %s\": NOT IN STARTING POSITION", komenda, y, x, kierunek, id, klasa);
            exit(0);
        }
        for (int i = 0; i < typ; i++) {
            if (i == 0) plansza[y][x + i] = '@';
            else if (i == typ - 1) plansza[y][x + i] = '%';
            else if (i == 1) plansza[y][x + i] = '!';
            else  plansza[y][x + i] = '+';
            //przypisanie do bazy lokalizacji dziala i silnika
            if (i == typ - 1) {
                if (kto == 'A')
                {
                    statekA.silnikY[id + dodaj] = y;
                    statekA.silnikX[id + dodaj] = x + i;
                }
                if (kto == 'B')
                {
                    statekB.silnikY[id + dodaj] = y;
                    statekB.silnikX[id + dodaj] = x + i;
                }
            }
            if (i == 1) {
                if (kto == 'A')
                {
                    statekA.dzialoY[id + dodaj] = y;
                    statekA.dzialoX[id + dodaj] = x + i;
                }
                if (kto == 'B')
                {
                    statekB.dzialoY[id + dodaj] = y;
                    statekB.dzialoX[id + dodaj] = x + i;
                }

            }
        }
        czujnik_rafa_statek(komenda, plansza, typ, kierunek, x, y, id, klasa, width, height, kto, mode, damage, 'X');
        if (mode == 1) {
            for (int i = 0; i < typ; i++)
            {
                if (damage[i] == '0') {
                    plansza[y][x + i] = 'x';
                    if (kto == 'A')zmien_stan('B');
                    else if (kto == 'B')zmien_stan('A');
                }
            }

        }
        break;
    }
    case 'N': {
        if ((kto == 'A' && y + typ - 1 > init_positions[3][0] && mode == 0) || (kto == 'B' && y + typ - 1 > init_positions[3][1] && mode == 0)) {
            printf("INVALID OPERATION \"%s %d %d %c %d %s\": NOT IN STARTING POSITION", komenda, y, x, kierunek, id, klasa);
            exit(0);
        }
        czujnik_rafa_statek(komenda, plansza, typ, kierunek, x, y, id, klasa, width, height, kto, mode, damage, 'X');
        for (int i = 0; i < typ; i++) {
            if (i == 0) plansza[y + i][x] = '@';
            else if (i == typ - 1) plansza[y + i][x] = '%';
            else if (i == 1) plansza[y + i][x] = '!';
            else  plansza[y + i][x] = '+';
            //przypisanie do bazy lokalizacji dziala i silnika
            if (i == typ - 1) {
                if (kto == 'A')
                {
                    statekA.silnikY[id + dodaj] = y + i;
                    statekA.silnikX[id + dodaj] = x;
                }
                if (kto == 'B')
                {
                    statekB.silnikY[id + dodaj] = y + i;
                    statekB.silnikX[id + dodaj] = x;
                }
            }
            if (i == 1) {
                if (kto == 'A')
                {
                    statekA.dzialoY[id + dodaj] = y + i;
                    statekA.dzialoX[id + dodaj] = x;
                }
                if (kto == 'B')
                {
                    statekB.dzialoY[id + dodaj] = y + i;
                    statekB.dzialoX[id + dodaj] = x;
                }

            }
        }
        if (mode == 1) {
            for (int i = 0; i < typ; i++)
            {
                if (damage[i] == '0') {
                    plansza[y + i][x] = 'x';
                    if (kto == 'A')zmien_stan('B');
                    else if (kto == 'B')zmien_stan('A');
                }
            }

        }
        break;
    }
    case 'E': {
        if ((kto == 'A' && x - typ + 1 < init_positions[0][0] && mode == 0) || (kto == 'B' && x - typ + 1 < init_positions[0][1] && mode == 0)) {
            printf("INVALID OPERATION \"%s %d %d %c %d %s\": NOT IN STARTING POSITION", komenda, y, x, kierunek, id, klasa);
            exit(0);
        }
        czujnik_rafa_statek(komenda, plansza, typ, kierunek, x, y, id, klasa, width, height, kto, mode, damage, 'X');
        for (int i = 0; i < typ; i++) {
            if (i == 0) plansza[y][x - i] = '@';
            else if (i == typ - 1) plansza[y][x - i] = '%';
            else if (i == 1) plansza[y][x - i] = '!';
            else  plansza[y][x - i] = '+';
            //przypisanie do bazy lokalizacji dziala i silnika
            if (i == typ - 1) {
                if (kto == 'A')
                {
                    statekA.silnikY[id + dodaj] = y;
                    statekA.silnikX[id + dodaj] = x - i;
                }
                if (kto == 'B')
                {
                    statekB.silnikY[id + dodaj] = y;
                    statekB.silnikX[id + dodaj] = x - i;
                }
            }
            if (i == 1) {
                if (kto == 'A')
                {
                    statekA.dzialoY[id + dodaj] = y;
                    statekA.dzialoX[id + dodaj] = x - i;
                }
                if (kto == 'B')
                {
                    statekB.dzialoY[id + dodaj] = y;
                    statekB.dzialoX[id + dodaj] = x - i;
                }

            }
        }
        if (mode == 1) {
            for (int i = 0; i < typ; i++)
            {
                if (damage[i] == '0') {
                    plansza[y][x - i] = 'x';
                    if (kto == 'A')zmien_stan('B');
                    else if (kto == 'B')zmien_stan('A');
                }
            }

        }

        break;
    }//gdy kierunek jest bledny
    default: {
        printf("INVALID OPERATION \"%s %d %d %c %d %s\": CHOOSE FROM [N]ORTH, [E]AST, [S]OUTH, [W]EST", komenda, y, x, kierunek, id, klasa);
        exit(0);
    }
    }
}
void szpieg(char kto, int* height, int* width) { //funckja dla komendy SPY

    int id, y, x;
    std::cin >> id >> y >> x;

    if (y >= *height || x >= *width || y < 0 || x < 0) { //SPY poza zakres mapy
        printf("INVALID OPERATION \"SPY %d %d %d\": FIELD DOES NOT EXIST", id, y, x);
        exit(0);
    }
    else if (id < 0 || id>MAX_FLEET_SIZE) {// bledny id carriera
        printf("INVALID OPERATION \"SPY %d %d %d\": INVALID CARRIER ID", id, y, x);
        exit(0);
    }
    else if (czywszystkiestatki() == 404) { //czy sa wszystkie statki na mapie
        printf("INVALID OPERATION \"SPY %d %d %d\": NOT ALL SHIPS PLACED", id, y, x);
        exit(0);
    }
    else if ((kto == 'A' && statekA.dzialo[id] == 1) || ((kto == 'B' && statekB.dzialo[id] == 1))) { //dzialo zniszczone
        printf("INVALID OPERATION \"SPY %d %d %d\": CANNOT SEND PLANE", id, y, x);
        exit(0);
    }
    else if ((kto == 'A' && statekA.id[id] == 0) || ((kto == 'B' && statekB.id[id] == 0))) { //brak statku o podanym id
        printf("INVALID OPERATION \"SPY %d %d %d\": CARRIER ID NOT FOUND", id, y, x);
        exit(0);
    }
    //przypisanie do bazy danych info o spy plane
    if (kto == 'A') {
        int spyID = statekA.limstrzal[0][1];
        statekA.spyX[spyID] = x;
        statekA.spyY[spyID] = y;
        statekA.spyID[spyID] = id + 1;
        statekA.limstrzal[0][1]++; //wyslanie spy plane licz jako strzal
    }
    else if (kto == 'B') {
        int spyID = statekB.limstrzal[0][1];
        statekB.spyX[spyID] = x;
        statekB.spyY[spyID] = y;
        statekB.spyID[spyID] = id + 1;
        statekB.limstrzal[0][1]++;
    }
    //przekroczonony limit strzalow/samolotow
    if ((kto == 'A' && (statekA.limstrzal[0][1] > statekA.limstrzal[0][0])) || ((kto == 'B' && (statekB.limstrzal[0][1] > statekB.limstrzal[0][0])))) {
        printf("INVALID OPERATION \"SPY %d %d %d\": ALL PLANES SENT", id, y, x);
        exit(0);
    }

}