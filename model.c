#include "model.h"

void FieldInit()
{
    Board[0][0] = 1; Board[0][1] = 2; Board[0][2] = 3; Board[0][3] = 4; Board[0][4] = 5;
        Board[0][5] = 6; Board[0][6] = 7; Board[0][7] = 8; Board[0][8] = 9;
    Board[1][0] = 4; Board[1][1] = 5; Board[1][2] = 6; Board[1][3] = 7; Board[1][4] = 8;
        Board[1][5] = 9; Board[1][6] = 1; Board[1][7] = 2; Board[1][8] = 3;
    Board[2][0] = 7; Board[2][1] = 8; Board[2][2] = 9; Board[2][3] = 1; Board[2][4] = 2;
        Board[2][5] = 3; Board[2][6] = 4; Board[2][7] = 5; Board[2][8] = 6;

    Board[3][0] = 2; Board[3][1] = 3; Board[3][2] = 4; Board[3][3] = 5; Board[3][4] = 6;
        Board[3][5] = 7; Board[3][6] = 8; Board[3][7] = 9; Board[3][8] = 1;
    Board[4][0] = 5; Board[4][1] = 6; Board[4][2] = 7; Board[4][3] = 8; Board[4][4] = 9;
        Board[4][5] = 1; Board[4][6] = 2; Board[4][7] = 3; Board[4][8] = 4;
    Board[5][0] = 8; Board[5][1] = 9; Board[5][2] = 1; Board[5][3] = 2; Board[5][4] = 3;
        Board[5][5] = 4; Board[5][6] = 5; Board[5][7] = 6; Board[5][8] = 7;

    Board[6][0] = 3; Board[6][1] = 4; Board[6][2] = 5; Board[6][3] = 6; Board[6][4] = 7;
        Board[6][5] = 8; Board[6][6] = 9; Board[6][7] = 1; Board[6][8] = 2;
    Board[7][0] = 6; Board[7][1] = 7; Board[7][2] = 8; Board[7][3] = 9; Board[7][4] = 1;
        Board[7][5] = 2; Board[7][6] = 3; Board[7][7] = 4; Board[7][8] = 5;
    Board[8][0] = 9; Board[8][1] = 1; Board[8][2] = 2; Board[8][3] = 3; Board[8][4] = 4;
        Board[8][5] = 5; Board[8][6] = 6; Board[8][7] = 7; Board[8][8] = 8;

    // перемешивание
    for(int i = 1; i < ROWS; i += 3) {
        ChangeTwoRows(i, rand() % 2 == 0 ? i + 1 : i - 1);
        ChangeTwoCols(i, rand() % 2 == 0 ? i + 1 : i - 1);
    }

    requestArrayForm();
    statusArrayForm();
}

void ChangeTwoRows(int a, int b)
{
    int tmp;
    for(int i = 0; i < ROWS; i++) {
        tmp = Board[a][i];
        Board[a][i] = Board[b][i];
        Board[b][i] = tmp;
    }
}

void ChangeTwoCols(int a, int b)
{
    int tmp;
    for(int i = 0; i < ROWS; i++) {
        tmp = Board[i][a];
        Board[i][a] = Board[i][b];
        Board[i][b] = tmp;
    }
}

void requestArrayForm()
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < ROWS; j++) {
            Request[i][j] = Board[i][j];
        }
    }

    int a, b;
    //int cellForRemov = 25 + diffLevel * 10;
    int cellForRemov = 10 + diffLevel * 10;
    //int cellForRemov  = 1;
    for(int i = 0; i < cellForRemov; i++) {
        a = rand() % 9;
        b = rand() % 9;
        Request[a][b] = 0;
    }
}

void statusArrayForm()
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < ROWS; j++) {
            Status[i][j] = Request[i][j] == 0 ? 0 : 1;
        }
    }
}

void statusArrayRequestDel()
{
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < ROWS; j++) {
            if (Status[i][j] == -1) {
                Status[i][j] =0;
                return;
            }
        }
    }
}

int isWinner()
{
    // проверка линий

    int i, j, k, i1, j1, flag;

    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < ROWS; j++) {
            if(Request[j][i] == 0) {
                return 0;
            }
        }
    }

    for(k = 1; k <= 9; k++) {

        for(i = 0; i < ROWS; i++) {
            flag = 0;
            for(j = 0; j < ROWS; j++) {
                if(Request[i][j] == k) {
                    flag++;
                }
            }
            if(flag != 1) return 0;
        }

        for(i = 0; i < ROWS; i++) {
            flag = 0;
            for(j = 0; j < ROWS; j++) {
                if(Request[j][i] == k) {
                    flag++;
                }
            }
            if(flag != 1) return 0;
        }


        for(i1 = 0; i1 < 3; i1++) {
            for(j1 = 0; j1 < 3; j1++) {
                flag = 0;
                for(i = i1 * 3; i < (i1 + 1) * 3; i++) {
                    for(j = j1 * 3; j < (j1 + 1) * 3; j++) {
                        if(Request[j][i] == k) {
                            flag++;
                        }
                    }
                }
            if(flag != 1) return 0;
            }
        }

    }


    return 1;
}

void useHelp()
{
    if(gameStatus == 0) {
        return;
    }

    if(helpItem == 0) {
        ShowNoHelp();
        FaceShow(6, diffLevel);
        return;
    }

    int a, b;
    int flag = 1;
    do{
        a = rand() % 9;
        b = rand() % 9;
        if (!Request[a][b]) {
            Request[a][b] = Board[a][b];
            flag = 0;
        }
    } while (flag);

    ShowAllBoard();
    FaceShow(9, 1);
    helpItem--;
    ShowStars(helpItem);

}




