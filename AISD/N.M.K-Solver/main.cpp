#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#define PLAYER_ONE 1
#define PLAYER_TWO 2

#define NO_CUTTING 0
#define CUT_IF_GAME_OVER 1

#define CONTINUE -2

#define TIE 0
#define WIN 1
#define LOSE -1

#define TWO_RISKS 2

#define INF 10

#define ZERO '0'

//n - number of colums m - number of rows
struct boardInfo {
    int n = 0, m = 0, k = 0;
    char currentPlayer;
    char** board = nullptr;
};

struct bestMove {
    int x = 0, y = 0;
};

int toInt(char a);
char opp(char player);
void genBoard(boardInfo& b);
void remBoard(boardInfo& b);
int checkDirections(boardInfo& b);
int countZeros(boardInfo& b);
int checkIfWin(boardInfo& b);
int checkRisks(boardInfo& b, char player);
bool checkField(boardInfo& b, int x, int y, char player);
bool checkIfValid(boardInfo& b, int x, int y);
int printWinner(int result);
int checkPlayerWin(int result, char player);
void printBoard(boardInfo& b);
bool cutIfGameOver(boardInfo& b);
void genAllPosMov(boardInfo& b, int mode);
int miniMax(boardInfo& b, char activePlayer);
void nextTurn(boardInfo& b);
void solveGameState(boardInfo& b);


int main() {


    std::clock_t time = std::clock();

    char command[35] = {};

    boardInfo b;

    while (true) {

        scanf("%34s", &command);

        if (feof(stdin) != 0) {
            break;
        }
        else if (!strcmp(command, "GEN_ALL_POS_MOV")) {
            genAllPosMov(b, NO_CUTTING);
        }
        else if (!strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER")) {
            genAllPosMov(b, CUT_IF_GAME_OVER);
        }
        else if (!strcmp(command, "SOLVE_GAME_STATE")) {
            solveGameState(b);
        }

    }

    remBoard(b);
    printf("%0.5fs", (std::clock() - time) / (double)CLOCKS_PER_SEC);
    return 0;
}

//converts player char to int
int toInt(char a) {
    return a - '0';
}
//returns opponent id
char opp(char player) {

    if (player == (PLAYER_ONE + '0')) {
        return PLAYER_TWO + '0';
    }
    return PLAYER_ONE + '0';
}
//generate board m - rows n - columns
void genBoard(boardInfo& b) {

    int _m, _n;

    scanf("%d %d %d %c", &_m, &_n, &b.k, &b.currentPlayer);

    if (b.m != _m || b.n != _n) {
        if (b.board != nullptr) remBoard(b);
        char** board = new char* [_m];

        for (int i = 0; i < _m; i++) {
            board[i] = new char[_n];
        }

        b.m = _m;
        b.n = _n;
        b.board = board;
    }
    for (int i = 0; i < _m; i++) {
        for (int j = 0; j < _n; j++) {
            scanf(" %c", &b.board[i][j]);
        }
    }
}
//remove board from memory
void remBoard(boardInfo& b) {

    for (int i = 0; i < b.m; i++) {
        delete[] b.board[i];
    }
    delete[] b.board;
    b.board = nullptr;
}

//function for checking win conditions returns 1,2 if win or 0 if nothing found
int checkDirections(boardInfo& b) {

    for (int y = 0; y < b.m; y++) {
        for (int x = 0; x < b.n; x++) {
            char flag = b.board[y][x];
            if (flag != ZERO) {
                bool diagonalUp = true, diagonalDown = true, vertical = true, horizontal = true;
                for (int checks = 1; (diagonalUp || diagonalDown ||
                    horizontal || vertical) && checks < b.k; checks++) {
                    //check down
                    if (y <= b.m - b.k) {
                        if (b.board[y + checks][x] != flag) vertical = false;
                    }
                    else vertical = false;
                    if (x <= b.n - b.k) {
                        //check left
                        if (b.board[y][x + checks] != flag) horizontal = false;
                        //check diagonal up
                        if (y >= b.k - 1) {
                            if (b.board[y - checks][x + checks] != flag) diagonalUp = false;
                        }
                        else diagonalUp = false;
                        //check diagonal down
                        if (y <= b.m - b.k) {
                            if (b.board[y + checks][x + checks] != flag) diagonalDown = false;
                        }
                        else diagonalDown = false;
                    }
                    else {
                        horizontal = false; diagonalDown = false; diagonalUp = false;
                    }
                }
                if (diagonalUp || diagonalDown || horizontal || vertical) {
                    return toInt(flag);
                }
            }
        }
    }
    return 0;
}

//returns amount of possible moves
int countZeros(boardInfo& b) {

    int amount = 0;
    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            if (b.board[i][j] == ZERO) {
                amount++;
            }
        }
    }
    return amount;
}

//returns 1,2 - winner TIE - if board is full or CONTINUE - nothing found
int checkIfWin(boardInfo& b) {

    int result = checkDirections(b);

    if (!result) {
        if (!countZeros(b)) {
            result = TIE;
        }
        else {
            result = CONTINUE;
        }
    }

    return result;
}
//returns 1 if player has one winning move or -1 if opponent has two
int checkRisks(boardInfo& b, char player) {

    int amount = 0;

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n && amount < TWO_RISKS; j++) {
            if (b.board[i][j] == ZERO) {
                if (checkField(b, j, i, player)) {
                    b.board[i][j] = player;
                    int result = checkDirections(b);
                    if (result == toInt(b.currentPlayer)) {
                        b.board[i][j] = ZERO;
                        return 1;
                    }
                    else if (result == toInt(opp(b.currentPlayer))) {
                        b.board[i][j] = ZERO;
                        return -1;
                    }
                    b.board[i][j] = opp(player);
                    if (checkDirections(b) == opp(player)) {
                        amount++;
                    }
                    b.board[i][j] = ZERO;
                }
            }
        }
    }

    if (amount == TWO_RISKS) {
        if (player == b.currentPlayer) {
            return 1;
        }
        else {
            return -1;
        }
    }

    return 0;
}
//returns true if only one surronding field has player's sign
bool checkField(boardInfo& b, int x, int y, char player) {

    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if ((i || j) && checkIfValid(b, x + j, y + i) && b.board[y + i][x + j] == player) {
                return true;
            }
        }
    }
    return false;
}
//check if coords are in board
bool checkIfValid(boardInfo& b, int x, int y) {

    return b.m > y && b.n > x && x >= 0 && y >= 0;
}
//print end condtion
int printWinner(int result) {

    switch (result) {
    case PLAYER_ONE: {
        printf("FIRST_PLAYER_WINS\n");
        break;
    }
    case PLAYER_TWO: {
        printf("SECOND_PLAYER_WINS\n");
        break;
    }
    case TIE: {
        printf("BOTH_PLAYERS_TIE\n");
        break;
    }
    }

    return result;
}
//returns WIN if player won or LOSE if a player lost
int checkPlayerWin(int result, char player) {

    if (toInt(player) == result) {
        result = WIN;
    }
    else if (toInt(opp(player)) == result) {
        result = LOSE;
    }

    return result;
}

void printBoard(boardInfo& b) {

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            printf("%c ", b.board[i][j]);
        }
        printf("\n");
    }
}

//returns true if current player has winning move
bool cutIfGameOver(boardInfo& b) {

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n; j++) {
            if (b.board[i][j] == ZERO) {
                b.board[i][j] = b.currentPlayer;
                if (checkDirections(b) == toInt(b.currentPlayer)) {
                    return true;
                }
                b.board[i][j] = ZERO;
            }
        }
    }

    return false;
}

//generate all possible moves and print them
void genAllPosMov(boardInfo& b, int mode) {

    genBoard(b);

    if (checkIfWin(b) != CONTINUE) {
        printf("0\n");
    }
    else if (mode == CUT_IF_GAME_OVER && cutIfGameOver(b)) {
        printf("1\n");
        printBoard(b);
    }
    else {
        int x = countZeros(b);
        printf("%d\n", x);
        for (int i = 0; i < b.m; i++) {
            for (int j = 0; j < b.n; j++) {
                if (b.board[i][j] == ZERO) {
                    b.board[i][j] = b.currentPlayer;
                    printBoard(b);
                    b.board[i][j] = ZERO;
                }
            }
        }
    }

}

//minimax algorithm
int miniMax(boardInfo& b, char activePlayer) {

    //check win condition
    int condition = checkPlayerWin(checkIfWin(b), b.currentPlayer);

    if (condition == WIN || condition == LOSE || condition == TIE) {
        return condition;
    }
    //check k-1 sequence
    condition = checkRisks(b, activePlayer);

    if (condition == WIN || condition == LOSE) {
        return condition;
    }

    //max
    if (activePlayer == b.currentPlayer) {
        int bestScore = -INF;
        for (int i = 0; i < b.m; i++) {
            for (int j = 0; j < b.n; j++) {
                if (b.board[i][j] == ZERO) {
                    b.board[i][j] = b.currentPlayer;
                    int score = miniMax(b, opp(b.currentPlayer));
                    b.board[i][j] = ZERO;
                    if (score == 1) return score;
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    //min
    else {
        int bestScore = INF;
        for (int i = 0; i < b.m; i++) {
            for (int j = 0; j < b.n; j++) {
                if (b.board[i][j] == ZERO) {
                    b.board[i][j] = activePlayer;
                    int score = miniMax(b, b.currentPlayer);
                    b.board[i][j] = ZERO;
                    if (score == -1) return score;
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}
//handles turns for players
void nextTurn(boardInfo& b) {

    int condition = checkRisks(b, b.currentPlayer);

    if (condition == WIN) {
        printWinner(toInt(b.currentPlayer));
        return;
    }
    else if (condition == LOSE) {
        printWinner(toInt(opp(b.currentPlayer)));
        return;
    }

    int bestScore = -INF;

    bestMove best;

    for (int i = 0; i < b.m; i++) {
        for (int j = 0; j < b.n && bestScore != 1; j++) {
            if (b.board[i][j] == ZERO) {
                b.board[i][j] = b.currentPlayer;
                int score = miniMax(b, opp(b.currentPlayer));
                b.board[i][j] = ZERO;
                if (score > bestScore) {
                    bestScore = score;
                    best.y = i;
                    best.x = j;
                }
            }
        }
    }

    b.board[best.y][best.x] = b.currentPlayer;

    if (printWinner(checkIfWin(b)) == CONTINUE) {
        b.currentPlayer = opp(b.currentPlayer);
        nextTurn(b);
    }
}
//generates board and starts a game
void solveGameState(boardInfo& b) {

    genBoard(b);

    if (printWinner(checkIfWin(b)) == CONTINUE) {
        nextTurn(b);
    }
}